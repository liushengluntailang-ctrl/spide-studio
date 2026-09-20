#include "Explorer.h"

#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QTreeView>
#include <QVBoxLayout>

Explorer::Explorer(QWidget *parent) : QWidget(parent), model(new QFileSystemModel(this)), tree(new QTreeView(this))
{
    model->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    tree->setModel(model); tree->setHeaderHidden(true); tree->setAnimated(false); tree->setSortingEnabled(true);
    for (int i = 1; i < 4; ++i) tree->hideColumn(i);
    auto *buttons = new QHBoxLayout;
    auto *newFile = new QPushButton("+ File");
    auto *newFolder = new QPushButton("+ Folder");
    auto *rename = new QPushButton("Rename");
    auto *remove = new QPushButton("Delete");
    buttons->addWidget(newFile); buttons->addWidget(newFolder); buttons->addWidget(rename); buttons->addWidget(remove);
    connect(newFile, &QPushButton::clicked, this, &Explorer::createFile);
    connect(newFolder, &QPushButton::clicked, this, &Explorer::createFolder);
    connect(rename, &QPushButton::clicked, this, &Explorer::renameSelected);
    connect(remove, &QPushButton::clicked, this, &Explorer::deleteSelected);
    auto *layout = new QVBoxLayout(this); layout->setContentsMargins(6, 6, 6, 6); layout->addLayout(buttons); layout->addWidget(tree);
    connect(tree, &QTreeView::doubleClicked, this, [this](const QModelIndex &index) { if (!model->isDir(index)) emit fileActivated(model->filePath(index)); });
}
void Explorer::setRootPath(const QString &path) { projectPath = path; tree->setRootIndex(model->setRootPath(path)); }
QString Explorer::rootPath() const { return projectPath; }
QString Explorer::selectedPath() const { const auto index = tree->currentIndex(); return index.isValid() ? model->filePath(index) : projectPath; }
void Explorer::openFolder()
{
    const QString path = QFileDialog::getExistingDirectory(this, tr("Open Project Folder"), projectPath);
    if (!path.isEmpty()) { setRootPath(path); }
}
void Explorer::createFile()
{
    const QString base = QFileInfo(selectedPath()).isDir() ? selectedPath() : QFileInfo(selectedPath()).absolutePath();
    bool ok = false; const QString name = QInputDialog::getText(this, tr("New File"), tr("File name:"), QLineEdit::Normal, QString(), &ok);
    if (ok && !name.isEmpty()) { QFile file(QDir(base).filePath(name)); file.open(QIODevice::WriteOnly); }
}
void Explorer::createFolder()
{
    const QString base = QFileInfo(selectedPath()).isDir() ? selectedPath() : QFileInfo(selectedPath()).absolutePath();
    bool ok = false; const QString name = QInputDialog::getText(this, tr("New Folder"), tr("Folder name:"), QLineEdit::Normal, QString(), &ok);
    if (ok && !name.isEmpty()) QDir(base).mkdir(name);
}
void Explorer::deleteSelected()
{
    const QString path = selectedPath(); if (path == projectPath || path.isEmpty()) return;
    if (QMessageBox::question(this, tr("Delete"), tr("Delete %1?").arg(QFileInfo(path).fileName())) != QMessageBox::Yes) return;
    QFileInfo info(path); if (info.isDir()) QDir(path).removeRecursively(); else QFile::remove(path);
}
void Explorer::renameSelected()
{
    const QString path = selectedPath(); if (path == projectPath || path.isEmpty()) return;
    bool ok = false; const QString name = QInputDialog::getText(this, tr("Rename"), tr("New name:"), QLineEdit::Normal, QFileInfo(path).fileName(), &ok);
    if (ok && !name.isEmpty()) QDir().rename(path, QDir(QFileInfo(path).absolutePath()).filePath(name));
}