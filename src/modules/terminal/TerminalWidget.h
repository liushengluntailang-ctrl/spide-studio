#pragma once
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QProcess>
#include <QWidget>

namespace Spide::Modules::Terminal {

class TerminalWidget : public QWidget {
    Q_OBJECT
public:
    explicit TerminalWidget(QWidget* parent = nullptr);
    void setWorkingDirectory(const QString& path);

private slots:
    void executeCommand();
    void onReadyRead();

private:
    QPlainTextEdit* m_output;
    QLineEdit* m_input;
    QProcess m_process;
    QString m_workingDir;
};

} // namespace Spide::Modules::Terminal
