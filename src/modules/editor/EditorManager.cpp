#include "EditorManager.h"
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

namespace Spide::Modules::Editor {

EditorManager::EditorManager(QWidget* parent) : QTabWidget(parent) {
    setTabsClosable(true);
    setMovable(true);
    setDocumentMode(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &EditorManager::closeTab);
    connect(this, &QTabWidget::currentChanged, this, &EditorManager::onCurrentTabChanged);
}

CodeEditor* EditorManager::currentEditor() const {
    return qobject_cast<CodeEditor*>(currentWidget());
}

CodeEditor* EditorManager::createEditor(const QString& filePath, const QString& content) {
    auto* editor = new CodeEditor(this);
    editor->setPlainText(content);
    editor->setFilePath(filePath);
    editor->document()->setModified(false);

    connect(editor, &CodeEditor::cursorPositionChangedInfo, this, &EditorManager::cursorChanged);
    connect(editor->document(), &QTextDocument::modificationChanged, this, &EditorManager::onDocumentModificationChanged);
    return editor;
}

bool EditorManager::openFile(const QString& filePath) {
    for (int i = 0; i < count(); ++i) {
        if (auto* editor = qobject_cast<CodeEditor*>(widget(i))) {
            if (editor->filePath() == filePath) {
                setCurrentIndex(i);
                return true;
            }
        }
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file:\n%1").arg(filePath));
        return false;
    }
    QTextStream in(&file);
    QString content = in.readAll();
    file.close();

    CodeEditor* editor = createEditor(filePath, content);
    int idx = addTab(editor, QFileInfo(filePath).fileName());
    setCurrentIndex(idx);
    return true;
}

bool EditorManager::saveCurrentFile() {
    auto* editor = currentEditor();
    if (!editor) return false;
    if (editor->filePath().isEmpty()) return saveCurrentFileAs();

    QFile file(editor->filePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Could not save file:\n%1").arg(editor->filePath()));
        return false;
    }
    QTextStream out(&file);
    out << editor->toPlainText();
    file.close();

    editor->document()->setModified(false);
    updateTabTitle(currentIndex());
    emit fileSaved(editor->filePath());
    return true;
}

bool EditorManager::saveCurrentFileAs() {
    auto* editor = currentEditor();
    if (!editor) return false;
    QString defaultPath = editor->filePath().isEmpty() ? "untitled.txt" : editor->filePath();
    QString path = QFileDialog::getSaveFileName(this, tr("Save File As"), defaultPath);
    if (path.isEmpty()) return false;

    editor->setFilePath(path);
    return saveCurrentFile();
}

bool EditorManager::saveAll() {
    bool ok = true;
    for (int i = 0; i < count(); ++i) {
        if (auto* editor = qobject_cast<CodeEditor*>(widget(i))) {
            if (editor->document()->isModified()) {
                setCurrentIndex(i);
                if (!saveCurrentFile()) ok = false;
            }
        }
    }
    return ok;
}

void EditorManager::closeTab(int index) {
    auto* editor = qobject_cast<CodeEditor*>(widget(index));
    if (!editor) return;

    if (editor->document()->isModified()) {
        QString title = tabText(index).remove('*');
        auto res = QMessageBox::question(
            this, tr("Unsaved Changes"),
            tr("Do you want to save the changes made to %1?").arg(title),
            QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        if (res == QMessageBox::Save) {
            setCurrentIndex(index);
            if (!saveCurrentFile()) return;
        } else if (res == QMessageBox::Cancel) {
            return;
        }
    }
    removeTab(index);
    delete editor;
}

void EditorManager::onCurrentTabChanged(int index) {
    if (index >= 0) {
        if (auto* editor = qobject_cast<CodeEditor*>(widget(index))) {
            QTextCursor cursor = editor->textCursor();
            emit cursorChanged(cursor.blockNumber() + 1, cursor.columnNumber() + 1);
        }
    }
}

void EditorManager::onDocumentModificationChanged(bool) {
    int idx = currentIndex();
    if (idx >= 0) updateTabTitle(idx);
}

void EditorManager::updateTabTitle(int index) {
    auto* editor = qobject_cast<CodeEditor*>(widget(index));
    if (!editor) return;
    QString name = editor->filePath().isEmpty() ? tr("Untitled") : QFileInfo(editor->filePath()).fileName();
    if (editor->document()->isModified()) name += "*";
    setTabText(index, name);
}

} // namespace Spide::Modules::Editor
