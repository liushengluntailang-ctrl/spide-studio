#include "ExplorerWidget.h"
#include <QDir>
#include <QFileInfo>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QVBoxLayout>

namespace Spide::Modules::Explorer {

ExplorerWidget::ExplorerWidget(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    m_treeView = new QTreeView(this);
    m_fileModel = new QFileSystemModel(this);
    m_fileModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

    m_treeView->setModel(m_fileModel);
    m_treeView->setHeaderHidden(true);
    for (int i = 1; i < m_fileModel->columnCount(); ++i) {
        m_treeView->hideColumn(i);
    }
    m_treeView->setAnimated(true);
    m_treeView->setIndentation(14);
    layout->addWidget(m_treeView);

    connect(m_treeView, &QTreeView::doubleClicked, this, &ExplorerWidget::onItemDoubleClicked);
}

void ExplorerWidget::setRootPath(const QString& path) {
    m_rootPath = path;
    QModelIndex rootIndex = m_fileModel->setRootPath(path);
    m_treeView->setRootIndex(rootIndex);
}

void ExplorerWidget::onItemDoubleClicked(const QModelIndex& index) {
    if (!index.isValid()) return;
    QString path = m_fileModel->filePath(index);
    if (QFileInfo(path).isFile()) emit fileSelected(path);
}

QString ExplorerWidget::getSelectedPath() const {
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return m_rootPath;
    return m_fileModel->filePath(index);
}

void ExplorerWidget::contextMenuEvent(QContextMenuEvent* event) {
    QMenu menu(this);
    menu.addAction(tr("New File..."), this, &ExplorerWidget::createNewFile);
    menu.addAction(tr("New Folder..."), this, &ExplorerWidget::createNewFolder);
    menu.addSeparator();

    if (m_treeView->currentIndex().isValid()) {
        menu.addAction(tr("Rename..."), this, &ExplorerWidget::renameSelectedItem);
        menu.addAction(tr("Delete"), this, &ExplorerWidget::deleteSelectedItem);
    }
    menu.exec(event->globalPos());
}

void ExplorerWidget::createNewFile() {
    QString targetDir = getSelectedPath();
    if (QFileInfo(targetDir).isFile()) targetDir = QFileInfo(targetDir).absolutePath();
    if (targetDir.isEmpty()) targetDir = m_rootPath;

    bool ok = false;
    QString name = QInputDialog::getText(this, tr("New File"), tr("File name:"), QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    QString newFilePath = QDir(targetDir).filePath(name.trimmed());
    QFile file(newFilePath);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::warning(this, tr("Error"), tr("Could not create file:\n%1").arg(newFilePath));
        return;
    }
    file.close();
    emit fileSelected(newFilePath);
}

void ExplorerWidget::createNewFolder() {
    QString targetDir = getSelectedPath();
    if (QFileInfo(targetDir).isFile()) targetDir = QFileInfo(targetDir).absolutePath();
    if (targetDir.isEmpty()) targetDir = m_rootPath;

    bool ok = false;
    QString name = QInputDialog::getText(this, tr("New Folder"), tr("Folder name:"), QLineEdit::Normal, "", &ok);
    if (!ok || name.trimmed().isEmpty()) return;

    QDir dir(targetDir);
    if (!dir.mkdir(name.trimmed())) {
        QMessageBox::warning(this, tr("Error"), tr("Could not create folder."));
    }
}

void ExplorerWidget::renameSelectedItem() {
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    QString oldPath = m_fileModel->filePath(index);
    QFileInfo fi(oldPath);
    bool ok = false;
    QString newName = QInputDialog::getText(this, tr("Rename"), tr("New name:"), QLineEdit::Normal, fi.fileName(), &ok);
    if (!ok || newName.trimmed().isEmpty() || newName == fi.fileName()) return;

    QString newPath = fi.dir().filePath(newName.trimmed());
    if (!QFile::rename(oldPath, newPath)) {
        QMessageBox::warning(this, tr("Error"), tr("Failed to rename item."));
    }
}

void ExplorerWidget::deleteSelectedItem() {
    QModelIndex index = m_treeView->currentIndex();
    if (!index.isValid()) return;
    QString path = m_fileModel->filePath(index);
    QFileInfo fi(path);

    auto reply = QMessageBox::question(this, tr("Confirm Delete"),
                                       tr("Are you sure you want to delete '%1'?").arg(fi.fileName()),
                                       QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if (fi.isDir()) QDir(path).removeRecursively();
        else QFile::remove(path);
    }
}

} // namespace Spide::Modules::Explorer
