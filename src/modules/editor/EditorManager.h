#pragma once
#include "CodeEditor.h"
#include <QTabWidget>

namespace Spide::Modules::Editor {

class EditorManager : public QTabWidget {
    Q_OBJECT
public:
    explicit EditorManager(QWidget* parent = nullptr);
    bool openFile(const QString& filePath);
    bool saveCurrentFile();
    bool saveCurrentFileAs();
    bool saveAll();
    CodeEditor* currentEditor() const;

signals:
    void cursorChanged(int line, int col);
    void fileSaved(const QString& filePath);

public slots:
    void closeTab(int index);

private slots:
    void onCurrentTabChanged(int index);
    void onDocumentModificationChanged(bool modified);

private:
    CodeEditor* createEditor(const QString& filePath, const QString& content);
    void updateTabTitle(int index);
};

} // namespace Spide::Modules::Editor
