#include "StatusBar.h"

namespace Spide::UI {

StatusBar::StatusBar(QWidget* parent) : QStatusBar(parent) {
    m_cursorLabel = new QLabel(tr("Ln 1, Col 1"), this);
    m_encodingLabel = new QLabel("UTF-8", this);
    addPermanentWidget(m_cursorLabel);
    addPermanentWidget(m_encodingLabel);
    showMessage(tr("Ready"), 3000);
}

void StatusBar::setCursorPosition(int line, int col) {
    m_cursorLabel->setText(QString("Ln %1, Col %2").arg(line).arg(col));
}

void StatusBar::setEncoding(const QString& encoding) {
    m_encodingLabel->setText(encoding);
}

} // namespace Spide::UI
