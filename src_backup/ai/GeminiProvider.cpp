#include "GeminiProvider.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>

GeminiProvider::GeminiProvider(QObject *parent) : IAIProvider(parent), model("gemini-3.1-pro-preview") {}
void GeminiProvider::sendMessage(const QString &message, const QString &context)
{
    if (apiKey.trimmed().isEmpty()) { emit errorOccurred("Gemini API key is not configured. Open Settings to add it."); return; }
    QUrl url(QString("https://generativelanguage.googleapis.com/v1beta/models/%1:generateContent").arg(model));
    QUrlQuery query; query.addQueryItem("key", apiKey); url.setQuery(query);
    QJsonObject part{{"text", context.isEmpty() ? message : QString("Project context:\n%1\n\nUser request:\n%2").arg(context, message)}};
    QJsonObject body{{"contents", QJsonArray{QJsonObject{{"parts", QJsonArray{part}}}}}};
    QNetworkRequest request(url); request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    auto *reply = network.post(request, QJsonDocument(body).toJson(QJsonDocument::Compact));
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        const QByteArray data = reply->readAll();
        if (reply->error() != QNetworkReply::NoError) emit errorOccurred(reply->errorString());
        else {
            const auto document = QJsonDocument::fromJson(data); const auto candidates = document.object().value("candidates").toArray();
            if (!candidates.isEmpty()) emit responseReady(candidates.first().toObject().value("content").toObject().value("parts").toArray().first().toObject().value("text").toString());
            else emit errorOccurred("Gemini returned an empty response.");
        }
        reply->deleteLater();
    });
}