#pragma once

#include <QProcess>
#include <QWidget>

class QLineEdit;
class QPlainTextEdit;

class Terminal : public QWidget
{
    Q_OBJECT
public:
    explicit Terminal(QWidget *parent = nullptr);
    void setWorkingDirectory(const QString &path);
    void setShell(const QString &path);
private slots:
    void runCommand();
private:
    QProcess process;
    QPlainTextEdit *output;
    QLineEdit *input;
    QString workingDirectory;
    QString shell;
};