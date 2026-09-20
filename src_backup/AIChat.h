#pragma once

#include <QWidget>

class IAIProvider;
class QPlainTextEdit;
class QLineEdit;

class AIChat : public QWidget
{
    Q_OBJECT
public:
    explicit AIChat(QWidget *parent = nullptr);
    void setProvider(IAIProvider *provider);
    void setContext(const QString &filePath, const QString &contents, const QString &selection = QString());
private slots:
    void sendMessage();
private:
    QPlainTextEdit *messages;
    QLineEdit *input;
    IAIProvider *provider = nullptr;
    QString filePath;
    QString contents;
    QString selection;
};