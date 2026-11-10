#include "TerminalWidget.h"
#include <QDir>
#include <QVBoxLayout>

namespace Spide::Modules::Terminal {

TerminalWidget::TerminalWidget(QWidget* parent)
    : QWidget(parent), m_workingDir(QDir::homePath()) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(4, 4, 4, 4);
    layout->setSpacing(4);

    m_output = new QPlainTextEdit(this);
    m_output->setObjectName("TerminalOutput");
    m_output->setReadOnly(true);

    m_input = new QLineEdit(this);
    m_input->setObjectName("TerminalInput");
    m_input->setPlaceholderText(tr("$ Enter terminal command..."));

    layout->addWidget(m_output);
    layout->addWidget(m_input);

    m_process.setProcessChannelMode(QProcess::MergedChannels);

    connect(m_input, &QLineEdit::returnPressed, this, &TerminalWidget::executeCommand);
    connect(&m_process, &QProcess::readyRead, this, &TerminalWidget::onReadyRead);
    connect(&m_process, &QProcess::finished, this, [this](int exitCode) {
        m_output->appendPlainText(QString("[Process finished with code %1]\n").arg(exitCode));
    });

    m_output->appendPlainText("SPIDE Studio Shell [Phase 1 Ready]\n");
}

void TerminalWidget::setWorkingDirectory(const QString& path) {
    m_workingDir = path;
    m_process.setWorkingDirectory(path);
}

void TerminalWidget::executeCommand() {
    QString cmd = m_input->text().trimmed();
    if (cmd.isEmpty()) return;

    m_output->appendPlainText(QString("$ %1").arg(cmd));
    m_input->clear();

#ifdef Q_OS_WIN
    m_process.start("cmd.exe", {"/C", cmd});
#else
    m_process.start("/bin/sh", {"-c", cmd});
#endif
}

void TerminalWidget::onReadyRead() {
    QByteArray data = m_process.readAll();
    m_output->insertPlainText(QString::fromLocal8Bit(data));
    m_output->ensureCursorVisible();
}

} // namespace Spide::Modules::Terminal
