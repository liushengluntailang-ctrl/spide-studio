#pragma once

#include <QPlainTextEdit>
#include <QSyntaxHighlighter>
#include <QTabWidget>

class LineNumberArea;

class CodeHighlighter : public QSyntaxHighlighter
{
public:
    explicit CodeHighlighter(QTextDocument *document);

protected:
    void highlightBlock(const QString &text) override;

private:
    QVector<QTextCharFormat> formats;
    QStringList keywords;
};

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
    friend class LineNumberArea;
public:
    explicit CodeEditor(QWidget *parent = nullptr);
    int lineNumberWidth() const;

signals:
    void cursorContextChanged(const QString &selection);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberAreaWidth(int newBlockCount);
    void updateLineNumberArea(const QRect &rect, int dy);
    void highlightCurrentLine();
    void emitSelection();

private:
    void paintLineNumbers(QPaintEvent *event);
    QWidget *lineNumberArea;
    CodeHighlighter *highlighter;
};

class Editor : public QTabWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = nullptr);
    bool openFile(const QString &filePath);
    bool saveCurrent();
    bool saveCurrentAs();
    QString currentFilePath() const;
    QString currentFileText() const;
    QString selectedText() const;

signals:
    void fileContextChanged(const QString &path, const QString &contents);
    void selectionChanged(const QString &selection);

private slots:
    void handleTabClose(int index);
    void updateTabTitle();
    void forwardSelection(const QString &selection);

private:
    int indexForPath(const QString &path) const;
    QString titleForPath(const QString &path) const;
};