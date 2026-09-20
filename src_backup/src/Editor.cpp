#include "Editor.h"

#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QRegularExpression>
#include <QScrollBar>
#include <QTextStream>

class LineNumberArea : public QWidget
{
public:
    explicit LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}
    QSize sizeHint() const override { return QSize(codeEditor->lineNumberWidth(), 0); }
protected:
    void paintEvent(QPaintEvent *event) override { codeEditor->paintLineNumbers(event); }
private:
    CodeEditor *codeEditor;
};

CodeHighlighter::CodeHighlighter(QTextDocument *document) : QSyntaxHighlighter(document)
{
    keywords = {"class", "struct", "public", "private", "protected", "if", "else", "for", "while", "return", "include", "import", "using", "namespace", "const", "auto", "void", "int", "bool", "nullptr", "true", "false", "def", "function", "let", "var", "const"};
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor("#c586c0"));
    keywordFormat.setFontWeight(QFont::Bold);
    for (const QString &keyword : keywords) {
        QTextCharFormat format = keywordFormat;
        Q_UNUSED(keyword);
        formats.append(format);
    }
}

void CodeHighlighter::highlightBlock(const QString &text)
{
    QTextCharFormat keywordFormat;
    keywordFormat.setForeground(QColor("#c586c0"));
    keywordFormat.setFontWeight(QFont::Bold);
    for (const QString &keyword : keywords) {
        QRegularExpression expression(QStringLiteral("\\b%1\\b").arg(QRegularExpression::escape(keyword)));
        auto match = expression.globalMatch(text);
        while (match.hasNext()) {
            const auto result = match.next();
            setFormat(result.capturedStart(), result.capturedLength(), keywordFormat);
        }
    }
    QTextCharFormat commentFormat;
    commentFormat.setForeground(QColor("#6a9955"));
    setFormat(text.indexOf("//"), text.size(), commentFormat);
    QTextCharFormat stringFormat;
    stringFormat.setForeground(QColor("#ce9178"));
    auto strings = QRegularExpression("(\\\"[^\\\"]*\\\"|'[^']*')").globalMatch(text);
    while (strings.hasNext()) {
        const auto match = strings.next();
        setFormat(match.capturedStart(), match.capturedLength(), stringFormat);
    }
}

CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent), lineNumberArea(new LineNumberArea(this)), highlighter(new CodeHighlighter(document()))
{
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    setTabStopDistance(fontMetrics().horizontalAdvance(' ') * 4);
    setLineWrapMode(QPlainTextEdit::NoWrap);
    connect(this, &QPlainTextEdit::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &QPlainTextEdit::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &QPlainTextEdit::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &QPlainTextEdit::selectionChanged, this, &CodeEditor::emitSelection);
    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberWidth() const
{
    int digits = 1;
    int maximum = qMax(1, blockCount());
    while (maximum >= 10) { maximum /= 10; ++digits; }
    return 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
}

void CodeEditor::updateLineNumberAreaWidth(int) { setViewportMargins(lineNumberWidth(), 0, 0, 0); }
void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy) lineNumberArea->scroll(0, dy); else lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    if (rect.contains(viewport()->rect())) updateLineNumberAreaWidth(0);
}
void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> selections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(QColor("#202a36"));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        selections.append(selection);
    }
    setExtraSelections(selections);
}
void CodeEditor::emitSelection() { emit cursorContextChanged(textCursor().selectedText()); }
void CodeEditor::resizeEvent(QResizeEvent *event)
{
    QPlainTextEdit::resizeEvent(event);
    QRect contents = contentsRect();
    lineNumberArea->setGeometry(QRect(contents.left(), contents.top(), lineNumberWidth(), contents.height()));
}
void CodeEditor::paintLineNumbers(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#151a21"));
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());
    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            painter.setPen(blockNumber == textCursor().blockNumber() ? QColor("#e6edf3") : QColor("#6e7681"));
            painter.drawText(0, top, lineNumberArea->width() - 6, fontMetrics().height(), Qt::AlignRight, QString::number(blockNumber + 1));
        }
        block = block.next(); top = bottom; bottom = top + qRound(blockBoundingRect(block).height()); ++blockNumber;
    }
}

Editor::Editor(QWidget *parent) : QTabWidget(parent)
{
    setTabsClosable(true);
    setMovable(true);
    connect(this, &QTabWidget::tabCloseRequested, this, &Editor::handleTabClose);
    connect(this, &QTabWidget::currentChanged, this, &Editor::updateTabTitle);
}

QString Editor::titleForPath(const QString &path) const
{
    return QFileInfo(path).fileName() + (path.isEmpty() ? QString() : QString());
}
int Editor::indexForPath(const QString &path) const
{
    for (int index = 0; index < count(); ++index) if (tabToolTip(index) == path) return index;
    return -1;
}
bool Editor::openFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return false;
    const int existing = indexForPath(filePath);
    if (existing >= 0) { setCurrentIndex(existing); return true; }
    auto *editor = new CodeEditor;
    editor->setPlainText(QString::fromUtf8(file.readAll()));
    editor->document()->setModified(false);
    const int index = addTab(editor, titleForPath(filePath));
    setTabToolTip(index, filePath);
    setCurrentIndex(index);
    connect(editor->document(), &QTextDocument::modificationChanged, this, &Editor::updateTabTitle);
    connect(editor, &CodeEditor::cursorContextChanged, this, &Editor::forwardSelection);
    emit fileContextChanged(filePath, editor->toPlainText());
    return true;
}
bool Editor::saveCurrent()
{
    if (currentIndex() < 0) return false;
    QString path = currentFilePath();
    if (path.isEmpty()) return saveCurrentAs();
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return false;
    QTextStream stream(&file); stream << qobject_cast<CodeEditor *>(currentWidget())->toPlainText();
    qobject_cast<CodeEditor *>(currentWidget())->document()->setModified(false);
    emit fileContextChanged(path, currentFileText());
    updateTabTitle();
    return true;
}
bool Editor::saveCurrentAs()
{
    if (currentIndex() < 0) return false;
    const QString path = QFileDialog::getSaveFileName(this, tr("Save File"));
    if (path.isEmpty()) return false;
    setTabToolTip(currentIndex(), path); setTabText(currentIndex(), titleForPath(path));
    return saveCurrent();
}
QString Editor::currentFilePath() const { return currentIndex() >= 0 ? tabToolTip(currentIndex()) : QString(); }
QString Editor::currentFileText() const { auto *editor = qobject_cast<CodeEditor *>(currentWidget()); return editor ? editor->toPlainText() : QString(); }
QString Editor::selectedText() const { auto *editor = qobject_cast<CodeEditor *>(currentWidget()); return editor ? editor->textCursor().selectedText() : QString(); }
void Editor::handleTabClose(int index)
{
    auto *editor = qobject_cast<CodeEditor *>(widget(index));
    if (editor && editor->document()->isModified()) {
        const auto choice = QMessageBox::question(this, tr("Unsaved Changes"), tr("Save changes to %1?").arg(tabText(index)), QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (choice == QMessageBox::Cancel) return;
        if (choice == QMessageBox::Save) { setCurrentIndex(index); if (!saveCurrent()) return; }
    }
    delete widget(index); removeTab(index);
}
void Editor::updateTabTitle()
{
    if (currentIndex() < 0) return;
    auto *editor = qobject_cast<CodeEditor *>(currentWidget());
    if (!editor) return;
    const QString title = titleForPath(currentFilePath()) + (editor->document()->isModified() ? " *" : "");
    setTabText(currentIndex(), title);
    emit fileContextChanged(currentFilePath(), editor->toPlainText());
}
void Editor::forwardSelection(const QString &selection) { emit selectionChanged(selection); }