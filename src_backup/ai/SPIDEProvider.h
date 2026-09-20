#pragma once

#include "IAIProvider.h"

#include <QNetworkAccessManager>
#include <QPointer>

class QNetworkReply;

class SPIDEProvider : public IAIProvider
{
    Q_OBJECT

public:
    explicit SPIDEProvider(QObject *parent = nullptr);

    QString providerName() const override
    {
        return "SPIDE";
    }

    void setServerUrl(const QString &url);
    QString serverUrl() const
    {
        return endpoint;
    }

    void setToken(const QString &value)
    {
        token = value;
    }

    void setModel(const QString &value)
    {
        model = value;
    }

    QString modelName() const
    {
        return model;
    }

    void sendMessage(
        const QString &message,
        const QString &context) override;

    void cancelRequest() override;

private:
    QNetworkAccessManager network;
    QPointer<QNetworkReply> currentReply;

    QString endpoint;
    QString token;
    QString model;
};