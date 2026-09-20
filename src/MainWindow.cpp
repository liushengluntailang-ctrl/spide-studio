#include "MainWindow.h"
#include "AIChat.h"
#include "Editor.h"
#include "Explorer.h"
#include "Settings.h"
#include "Terminal.h"
#include "ai/SPIDEProvider.h"

#include <QApplication>
#include <QDir>
#include <QFileDialog>
#include <QFileInfo>
#include <QPlainTextEdit>
#include <QSettings>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      explorer(new Explorer(this)),
      editor(new Editor(this)),
      terminal(new Terminal(this)),
      aiChat(new AIChat(this)),
      spide(new SPIDEProvider(this))
{
    setWindowTitle("SPIDE Studio");
    resize(1440, 900);

    auto *mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->addWidget(explorer);
    mainSplitter->addWidget(editor);
    mainSplitter->addWidget(aiChat);
    mainSplitter->setStretchFactor(1, 1);
    mainSplitter->setSizes({240, 760, 360});

    auto *bottom = new QTabWidget;
    bottom->addTab(terminal, "Terminal");
    bottom->addTab(new QPlainTextEdit("Problems will appear here."), "Problems");
    bottom->addTab(new QPlainTextEdit("Build and application output will appear here."), "Output");

    auto *vertical = new QSplitter(Qt::Vertical);
    vertical->addWidget(mainSplitter);
    vertical->addWidget(bottom);
    vertical->setStretchFactor(0, 1);
    vertical->setSizes({680, 220});

    setCentralWidget(vertical);

    auto *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(
        "Open Project...",
        this,
        &MainWindow::openProject,
        QKeySequence("Ctrl+Shift+O")
    );

    fileMenu->addAction(
        "Open File...",
        this,
        [this] {
            const QString path =
                QFileDialog::getOpenFileName(this, "Open File", projectPath);
            if (!path.isEmpty())
                editor->openFile(path);
        },
        QKeySequence::Open
    );

    fileMenu->addAction(
        "Save",
        editor,
        &Editor::saveCurrent,
        QKeySequence::Save
    );

    fileMenu->addAction(
        "Save As...",
        editor,
        &Editor::saveCurrentAs
    );

    fileMenu->addSeparator();
    fileMenu->addAction("Quit", qApp, &QApplication::quit, QKeySequence::Quit);

    auto *viewMenu = menuBar()->addMenu("View");
    viewMenu->addAction("Settings...", this, &MainWindow::showSettings);

    auto *helpMenu = menuBar()->addMenu("Help");
    helpMenu->addAction(
        "About SPIDE Studio",
        this,
        [this] {
            statusBar()->showMessage(
                "SPIDE Studio v0.1 - C++20 / Qt 6 / SPIDE AI",
                3000
            );
        }
    );

    statusBar()->showMessage("Open a project folder to begin");

    connect(
        explorer,
        &Explorer::fileActivated,
        editor,
        &Editor::openFile
    );

    connect(
        editor,
        &Editor::fileContextChanged,
        this,
        [this](const QString &, const QString &) {
            updateAIContext();
        }
    );

    connect(
        editor,
        &Editor::selectionChanged,
        this,
        &MainWindow::updateAIContext
    );

    aiChat->setProvider(spide);

    setProjectPath(QDir::homePath());
    applySettings();
}

void MainWindow::applySettings()
{
    QSettings settings;

    spide->setServerUrl(
        settings.value(
            "spide/serverUrl",
            "http://localhost:8000/v1/chat/completions"
        ).toString()
    );

    spide->setToken(
        settings.value("spide/token").toString()
    );

    spide->setModel(
        settings.value("spide/model", "spide-speed-0.3").toString()
    );

    terminal->setShell(
        settings.value("terminal/shell", "/bin/bash").toString()
    );
}

void MainWindow::setProjectPath(const QString &path)
{
    projectPath = path;
    explorer->setRootPath(path);
    terminal->setWorkingDirectory(path);

    setWindowTitle(
        QString("SPIDE Studio - %1")
            .arg(QFileInfo(path).fileName())
    );
}

void MainWindow::openProject()
{
    const QString path =
        QFileDialog::getExistingDirectory(
            this,
            "Open Project Folder",
            projectPath
        );

    if (!path.isEmpty())
        setProjectPath(path);
}

void MainWindow::showSettings()
{
    Settings dialog(this);

    connect(
        &dialog,
        &Settings::settingsChanged,
        this,
        [this] {
            applySettings();
        }
    );

    dialog.exec();
}

void MainWindow::updateAIContext()
{
    aiChat->setContext(
        editor->currentFilePath(),
        editor->currentFileText(),
        editor->selectedText()
    );
}
