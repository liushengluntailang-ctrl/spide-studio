#include "Terminal.h"

#include <QDir>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

Terminal::Terminal(QWidget *parent) : QWidget(parent), output(new QPlainTextEdit(this)), input(new QLineEdit(this)), shell("/bin/sh")
{
    output->setReadOnly(true); output->setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont)); input->setPlaceholderText("Enter command...");
    auto *run = new QPushButton(tr("Run")); auto *line = new QHBoxLayout; line->addWidget(input); line->addWidget(run);
    auto *layout = new QVBoxLayout(this); layout->setContentsMargins(4, 4, 4, 4); layout->addWidget(output); layout->addLayout(line);
    connect(run, &QPushButton::clicked, this, &Terminal::runCommand); connect(input, &QLineEdit::returnPressed, this, &Terminal::runCommand);
    connect(&process, &QProcess::readyReadStandardOutput, this, [this] { output->insertPlainText(QString::fromLocal8Bit(process.readAllStandardOutput())); output->ensureCursorVisible(); });
    connect(&process, &QProcess::readyReadStandardError, this, [this] { output->insertPlainText(QString::fromLocal8Bit(process.readAllStandardError())); output->ensureCursorVisible(); });
    connect(&process, &QProcess::finished, this, [this](int code) { output->appendPlainText(QString("\n[process exited with code %1]").arg(code)); });
}
void Terminal::setWorkingDirectory(const QString &path) { workingDirectory = path; process.setWorkingDirectory(path); }
void Terminal::setShell(const QString &path) { if (!path.trimmed().isEmpty()) shell = path.trimmed(); }
void Terminal::runCommand()
{
    const QString command = input->text().trimmed(); if (command.isEmpty()) return;
    output->appendPlainText(QString("$ %1").arg(command)); input->clear();
#ifdef Q_OS_WIN
    process.start("cmd.exe", {"/C", command});
#else
    process.start(shell, {"-c", command});
#endif
}