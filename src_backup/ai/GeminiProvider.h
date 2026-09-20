#pragma once

#include "IAIProvider.h"
#include <QNetworkAccessManager>

class GeminiProvider : public IAIProvider
{
    Q_OBJECT
public:
    explicit GeminiProvider(QObject *parent = nullptr);
    QString providerName() const override { return "Gemini"; }
    void setApiKey(const QString &key) { apiKey = key; }
    void setModel(const QString &value) { model = value; }
    void sendMessage(const QString &message, const QString &context) override;
private:
    QNetworkAccessManager network;
    QString apiKey;
    QString model;
};