#pragma once

#include <QObject>
#include <QString>

class IAIProvider : public QObject
{
    Q_OBJECT
public:
    explicit IAIProvider(QObject *parent = nullptr) : QObject(parent) {}
    ~IAIProvider() override = default;

    virtual QString providerName() const = 0;
    virtual void sendMessage(const QString &message, const QString &context) = 0;
    virtual void cancelRequest() = 0;

signals:
    void responseReady(const QString &response);
    void errorOccurred(const QString &message);
};
