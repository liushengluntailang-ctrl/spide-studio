#pragma once
#include <QPlainTextEdit>
#include <QWidget>

namespace Spide::Modules::Editor {

class CodeEditor;

class LineNumberArea : public QWidget {
public:
    explicit LineNumberArea(CodeEditor* editor);
    QSize sizeHint() const override;
protected:
    void paintEvent(QPaintEvent* event) override;
private:
    CodeEditor* m_editor;
};

class CodeEditor : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit CodeEditor(QWidget* parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent* event);
    int lineNumberAreaWidth() const;
    const QString& filePath() const { return m_filePath; }
    void setFilePath(const QString& path) { m_filePath = path; }

signals:
    void cursorPositionChangedInfo(int line, int col);

protected:
    void resizeEvent(QResizeEvent* event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect& rect, int dy);
    void onCursorPositionChanged();

private:
    QWidget* m_lineNumberArea;
    QString m_filePath;
};

} // namespace Spide::Modules::Editor
