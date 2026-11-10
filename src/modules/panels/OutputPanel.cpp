#include "OutputPanel.h"
#include <QDateTime>
#include <QVBoxLayout>

namespace Spide::Modules::Panels {

OutputPanel::OutputPanel(QWidget* parent) : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    m_logArea = new QPlainTextEdit(this);
    m_logArea->setReadOnly(true);
    layout->addWidget(m_logArea);
}

void OutputPanel::appendLog(const QString& message) {
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    m_logArea->appendPlainText(QString("[%1] %2").arg(timestamp, message));
}

void OutputPanel::clearLog() {
    m_logArea->clear();
}

} // namespace Spide::Modules::Panels
