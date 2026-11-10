#include "CodeEditor.h"
#include <QFontDatabase>
#include <QPainter>
#include <QTextBlock>

namespace Spide::Modules::Editor {

LineNumberArea::LineNumberArea(CodeEditor* editor) : QWidget(editor), m_editor(editor) {}
QSize LineNumberArea::sizeHint() const { return QSize(m_editor->lineNumberAreaWidth(), 0); }
void LineNumberArea::paintEvent(QPaintEvent* event) { m_editor->lineNumberAreaPaintEvent(event); }

CodeEditor::CodeEditor(QWidget* parent) : QPlainTextEdit(parent) {
    m_lineNumberArea = new LineNumberArea(this);
    setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));
    setLineWrapMode(NoWrap);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::onCursorPositionChanged);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth() const {
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) { max /= 10; ++digits; }
    return 18 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
}

void CodeEditor::updateLineNumberAreaWidth(int) { setViewportMargins(lineNumberAreaWidth(), 0, 0, 0); }

void CodeEditor::updateLineNumberArea(const QRect& rect, int dy) {
    if (dy) m_lineNumberArea->scroll(0, dy);
    else m_lineNumberArea->update(0, rect.y(), m_lineNumberArea->width(), rect.height());
    if (rect.contains(viewport()->rect())) updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent* event) {
    QPlainTextEdit::resizeEvent(event);
    QRect cr = contentsRect();
    m_lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine() {
    QList<QTextEdit::ExtraSelection> extraSelections;
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        selection.format.setBackground(QColor(42, 45, 52));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void CodeEditor::onCursorPositionChanged() {
    QTextCursor cursor = textCursor();
    emit cursorPositionChangedInfo(cursor.blockNumber() + 1, cursor.columnNumber() + 1);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent* event) {
    QPainter painter(m_lineNumberArea);
    painter.fillRect(event->rect(), QColor(28, 28, 28));
    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(blockNumber == textCursor().blockNumber() ? QColor("#ffffff") : QColor("#858585"));
            painter.drawText(0, top, m_lineNumberArea->width() - 6, fontMetrics().height(), Qt::AlignRight, number);
        }
        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

} // namespace Spide::Modules::Editor
