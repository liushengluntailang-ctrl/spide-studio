#include "MainWindow.h"
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMessageBox>

namespace Spide::UI {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_commands = new Core::CommandManager(this);
    setupUi();
    setupCommands();
    setupMenus();

    resize(1366, 820);
    setWindowTitle("SPIDE Studio");
}

void MainWindow::setupUi() {
    auto* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto* rootLayout = new QHBoxLayout(centralWidget);
    rootLayout->setContentsMargins(0, 0, 0, 0);
    rootLayout->setSpacing(0);

    m_activityBar = new ActivityBar(this);
    rootLayout->addWidget(m_activityBar);

    m_mainSplitter = new QSplitter(Qt::Horizontal, this);
    m_mainSplitter->setHandleWidth(1);

    m_sidebar = new Sidebar(this);
    m_mainSplitter->addWidget(m_sidebar);

    m_centerSplitter = new QSplitter(Qt::Vertical, this);
    m_centerSplitter->setHandleWidth(1);

    m_editorManager = new Modules::Editor::EditorManager(this);
    m_bottomPanel = new BottomPanel(this);

    m_centerSplitter->addWidget(m_editorManager);
    m_centerSplitter->addWidget(m_bottomPanel);
    m_centerSplitter->setStretchFactor(0, 3);
    m_centerSplitter->setStretchFactor(1, 1);

    m_mainSplitter->addWidget(m_centerSplitter);
    m_mainSplitter->setStretchFactor(0, 1);
    m_mainSplitter->setStretchFactor(1, 4);

    rootLayout->addWidget(m_mainSplitter);

    m_statusBar = new StatusBar(this);
    setStatusBar(m_statusBar);

    connect(m_sidebar->explorerWidget(), &Modules::Explorer::ExplorerWidget::fileSelected,
            m_editorManager, &Modules::Editor::EditorManager::openFile);
    connect(m_editorManager, &Modules::Editor::EditorManager::cursorChanged,
            m_statusBar, &StatusBar::setCursorPosition);
    connect(m_editorManager, &Modules::Editor::EditorManager::fileSaved, this, [this](const QString& path) {
        m_bottomPanel->outputPanel()->appendLog(tr("Saved: %1").arg(path));
        m_statusBar->showMessage(tr("Saved %1").arg(path), 3000);
    });
    connect(m_activityBar, &ActivityBar::activityChanged, this, [this](int id) {
        if (m_sidebar->isVisible() && m_lastSidebarId == id) {
            m_sidebar->hide();
        } else {
            m_sidebar->show();
            m_sidebar->setCurrentIndex(id);
            m_lastSidebarId = id;
        }
    });
}

void MainWindow::setupCommands() {
    m_commands->registerCommand("file.openFile", tr("&Open File..."), QKeySequence::Open, [this]() { onOpenFile(); });
    m_commands->registerCommand("file.openFolder", tr("Open &Folder..."), QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_O), [this]() { onOpenFolder(); });
    m_commands->registerCommand("file.save", tr("&Save"), QKeySequence::Save, [this]() { m_editorManager->saveCurrentFile(); });
    m_commands->registerCommand("file.saveAs", tr("Save &As..."), QKeySequence::SaveAs, [this]() { m_editorManager->saveCurrentFileAs(); });
    m_commands->registerCommand("file.saveAll", tr("Save A&ll"), QKeySequence(Qt::CTRL | Qt::ALT | Qt::Key_S), [this]() { m_editorManager->saveAll(); });
    m_commands->registerCommand("file.closeTab", tr("&Close Tab"), QKeySequence::Close, [this]() {
        int idx = m_editorManager->currentIndex();
        if (idx >= 0) m_editorManager->closeTab(idx);
    });
    m_commands->registerCommand("view.toggleSidebar", tr("Toggle &Sidebar"), QKeySequence(Qt::CTRL | Qt::Key_B), [this]() { toggleSidebar(); });
    m_commands->registerCommand("view.toggleBottomPanel", tr("Toggle &Panel"), QKeySequence(Qt::CTRL | Qt::Key_J), [this]() { toggleBottomPanel(); });
    m_commands->registerCommand("app.exit", tr("E&xit"), QKeySequence::Quit, [this]() { close(); });
}

void MainWindow::setupMenus() {
    auto* mb = menuBar();

    auto* fileMenu = mb->addMenu(tr("&File"));
    fileMenu->addAction(m_commands->getAction("file.openFile"));
    fileMenu->addAction(m_commands->getAction("file.openFolder"));
    fileMenu->addSeparator();
    fileMenu->addAction(m_commands->getAction("file.save"));
    fileMenu->addAction(m_commands->getAction("file.saveAs"));
    fileMenu->addAction(m_commands->getAction("file.saveAll"));
    fileMenu->addAction(m_commands->getAction("file.closeTab"));
    fileMenu->addSeparator();
    fileMenu->addAction(m_commands->getAction("app.exit"));

    auto* editMenu = mb->addMenu(tr("&Edit"));
    editMenu->addAction(tr("&Undo"), [this]() { if (auto* ed = m_editorManager->currentEditor()) ed->undo(); }, QKeySequence::Undo);
    editMenu->addAction(tr("&Redo"), [this]() { if (auto* ed = m_editorManager->currentEditor()) ed->redo(); }, QKeySequence::Redo);
    editMenu->addSeparator();
    editMenu->addAction(tr("Cu&t"), [this]() { if (auto* ed = m_editorManager->currentEditor()) ed->cut(); }, QKeySequence::Cut);
    editMenu->addAction(tr("&Copy"), [this]() { if (auto* ed = m_editorManager->currentEditor()) ed->copy(); }, QKeySequence::Copy);
    editMenu->addAction(tr("&Paste"), [this]() { if (auto* ed = m_editorManager->currentEditor()) ed->paste(); }, QKeySequence::Paste);

    auto* viewMenu = mb->addMenu(tr("&View"));
    viewMenu->addAction(m_commands->getAction("view.toggleSidebar"));
    viewMenu->addAction(m_commands->getAction("view.toggleBottomPanel"));

    auto* helpMenu = mb->addMenu(tr("&Help"));
    helpMenu->addAction(tr("&About SPIDE Studio"), [this]() {
        QMessageBox::about(this, tr("About SPIDE Studio"),
            tr("<h3>SPIDE Studio</h3><p>Phase 1: IDE Foundation</p><p>Native C++20 / Qt 6 IDE</p>"));
    });
}

void MainWindow::onOpenFile() {
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"));
    if (!path.isEmpty()) {
        m_editorManager->openFile(path);
        m_bottomPanel->outputPanel()->appendLog(tr("Opened: %1").arg(path));
    }
}

void MainWindow::onOpenFolder() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Folder"), QString(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        m_sidebar->explorerWidget()->setRootPath(dir);
        m_bottomPanel->terminalWidget()->setWorkingDirectory(dir);
        m_bottomPanel->outputPanel()->appendLog(tr("Opened folder: %1").arg(dir));
        setWindowTitle(QString("SPIDE Studio — %1").arg(QFileInfo(dir).fileName()));
    }
}

void MainWindow::toggleSidebar() {
    m_sidebar->setVisible(!m_sidebar->isVisible());
}

void MainWindow::toggleBottomPanel() {
    m_bottomPanel->setVisible(!m_bottomPanel->isVisible());
}

} // namespace Spide::UI
