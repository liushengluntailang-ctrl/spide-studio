#include "SPIDEProvider.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

SPIDEProvider::SPIDEProvider(QObject *parent)
    : IAIProvider(parent),
      endpoint("http://localhost:8000/v1/chat/completions"),
      model("spide-speed-0.3")
{
}

void SPIDEProvider::setServerUrl(const QString &url)
{
    endpoint = url.trimmed();
}

void SPIDEProvider::sendMessage(const QString &message, const QString &context)
{
    cancelRequest();

    if (endpoint.trimmed().isEmpty()) {
        emit errorOccurred("SPIDE Server URL is empty.");
        return;
    }

    if (model.trimmed().isEmpty()) {
        emit errorOccurred("SPIDE model is empty.");
        return;
    }

    QString prompt = message;
    if (!context.trimmed().isEmpty()) {
        prompt = QString(
            "You are SPIDE AI.\n"
            "Use the following project/editor context when it is relevant.\n\n"
            "=== CONTEXT ===\n%1\n=== END CONTEXT ===\n\n"
            "=== USER REQUEST ===\n%2\n=== END USER REQUEST ==="
        ).arg(context, message);
    }

    QJsonObject userMessage{
        {"role", "user"},
        {"content", prompt}
    };

    QJsonArray messages;
    messages.append(userMessage);

    QJsonObject body{
        {"model", model},
        {"messages", messages},
        {"stream", false}
    };

    QNetworkRequest request(QUrl(endpoint));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Accept", "application/json");

    if (!token.trimmed().isEmpty()) {
        request.setRawHeader("Authorization", QByteArray("Bearer ") + token.toUtf8());
    }

    currentReply = network.post(request, QJsonDocument(body).toJson(QJsonDocument::Compact));

    QPointer<QNetworkReply> reply = currentReply;
    connect(reply, &QNetworkReply::finished, this, [this, reply] {
        if (!reply) return;

        if (reply->property("spideCancelled").toBool()) {
            reply->deleteLater();
            return;
        }

        const QByteArray data = reply->readAll();

        if (reply->error() != QNetworkReply::NoError) {
            emit errorOccurred(
                QString("SPIDE Server error: %1\nHTTP status: %2")
                    .arg(reply->errorString())
                    .arg(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt())
            );
            reply->deleteLater();
            currentReply = nullptr;
            return;
        }

        QJsonParseError parseError;
        const QJsonDocument document = QJsonDocument::fromJson(data, &parseError);

        if (parseError.error != QJsonParseError::NoError || !document.isObject()) {
            emit errorOccurred(
                QString("SPIDE Server returned invalid JSON: %1")
                    .arg(parseError.errorString())
            );
            reply->deleteLater();
            currentReply = nullptr;
            return;
        }

        const QJsonObject root = document.object();
        QString answer;

        // OpenAI-compatible response:
        // {"choices":[{"message":{"content":"..."}}]}
        const QJsonArray choices = root.value("choices").toArray();
        if (!choices.isEmpty()) {
            const QJsonObject choice = choices.first().toObject();
            const QJsonObject msg = choice.value("message").toObject();
            answer = msg.value("content").toString();

            if (answer.isEmpty())
                answer = choice.value("text").toString();
        }

        // Simple SPIDE server response fallbacks.
        if (answer.isEmpty())
            answer = root.value("response").toString();

        if (answer.isEmpty())
            answer = root.value("text").toString();

        if (answer.isEmpty()) {
            const QJsonObject messageObject = root.value("message").toObject();
            answer = messageObject.value("content").toString();
        }

        if (answer.isEmpty()) {
            emit errorOccurred("SPIDE Server returned no text. Check the server response format.");
        } else {
            emit responseReady(answer);
        }

        reply->deleteLater();
        currentReply = nullptr;
    });
}

void SPIDEProvider::cancelRequest()
{
    if (!currentReply) return;

    currentReply->setProperty("spideCancelled", true);
    currentReply->abort();
    currentReply = nullptr;
}
