#include "SPIDEProvider.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

SPIDEProvider::SPIDEProvider(QObject *parent)
    : IAIProvider(parent),
      network(this),
      currentReply(nullptr)
{
}

void SPIDEProvider::sendMessage(
    const QString &message,
    const QString &context)
{
    cancelRequest();

    const QString endpointUrl = serverUrl();

    if (endpointUrl.isEmpty()) {
        emit errorOccurred(
            "SPIDE Server URL is empty."
        );
        return;
    }

    const QUrl url(endpointUrl);

    if (!url.isValid() || url.scheme().isEmpty()) {
        emit errorOccurred(
            QString("Invalid SPIDE Server URL: %1")
                .arg(endpointUrl)
        );
        return;
    }

    QNetworkRequest request{url};

    request.setHeader(
        QNetworkRequest::ContentTypeHeader,
        "application/json"
    );

    request.setRawHeader(
        "Accept",
        "application/json"
    );

    if (!token.isEmpty()) {
        request.setRawHeader(
            "Authorization",
            QByteArray("Bearer ") +
            token.toUtf8()
        );
    }

    QString prompt = message;

    if (!context.trimmed().isEmpty()) {
        prompt +=
            "\n\n===== PROJECT CONTEXT =====\n"
            + context +
            "\n===== END PROJECT CONTEXT =====";
    }

    /*
     * SPIDE model
     *
     * Speed       -> spide-speed-0.3
     * Null        -> spide-null-0.6
     * Null Pro    -> spide-null-pro-0.5
     */

    const QString selectedModel =
        model.isEmpty()
            ? QString("spide-speed-0.3")
            : model;

    QJsonObject userMessage;

    userMessage["role"] = "user";
    userMessage["content"] = prompt;

    QJsonArray messages;

    messages.append(userMessage);

    QJsonObject body;

    body["model"] = selectedModel;
    body["messages"] = messages;
    body["stream"] = false;

    const QByteArray data =
        QJsonDocument(body)
            .toJson(QJsonDocument::Compact);

    currentReply =
        network.post(request, data);

    if (!currentReply) {
        emit errorOccurred(
            "Failed to create network request."
        );
        return;
    }

    connect(
        currentReply,
        &QNetworkReply::finished,
        this,
        [this]()
        {
            if (!currentReply) {
                return;
            }

            QNetworkReply *reply =
                currentReply;

            currentReply = nullptr;

            if (reply->error() !=
                QNetworkReply::NoError)
            {
                const QString error =
                    reply->errorString();

                reply->deleteLater();

                emit errorOccurred(
                    QString(
                        "SPIDE Server error: %1"
                    ).arg(error)
                );

                return;
            }

            const QByteArray responseData =
                reply->readAll();

            reply->deleteLater();

            if (responseData.isEmpty()) {
                emit errorOccurred(
                    "SPIDE Server returned "
                    "an empty response."
                );
                return;
            }

            QJsonParseError parseError;

            const QJsonDocument document =
                QJsonDocument::fromJson(
                    responseData,
                    &parseError
                );

            if (parseError.error !=
                QJsonParseError::NoError)
            {
                emit errorOccurred(
                    QString(
                        "Invalid JSON response "
                        "from SPIDE Server: %1"
                    ).arg(
                        parseError.errorString()
                    )
                );

                return;
            }

            if (!document.isObject()) {
                emit errorOccurred(
                    "SPIDE Server response "
                    "is not a JSON object."
                );
                return;
            }

            const QJsonObject root =
                document.object();

            QString response;

            /*
             * OpenAI-compatible response
             *
             * {
             *   "choices": [
             *     {
             *       "message": {
             *         "content": "..."
             *       }
             *     }
             *   ]
             * }
             */

            const QJsonArray choices =
                root.value("choices")
                    .toArray();

            if (!choices.isEmpty()) {

                const QJsonObject choice =
                    choices.first().toObject();

                const QJsonObject messageObject =
                    choice.value("message")
                        .toObject();

                response =
                    messageObject
                        .value("content")
                        .toString();

                if (response.isEmpty()) {
                    response =
                        choice.value("text")
                            .toString();
                }
            }

            /*
             * SPIDE native/simple response
             */

            if (response.isEmpty()) {
                response =
                    root.value("response")
                        .toString();
            }

            if (response.isEmpty()) {
                response =
                    root.value("text")
                        .toString();
            }

            if (response.isEmpty()) {
                response =
                    root.value("message")
                        .toString();
            }

            if (response.isEmpty()) {
                emit errorOccurred(
                    "SPIDE Server returned JSON, "
                    "but no response text "
                    "was found."
                );

                return;
            }

            emit responseReady(response);
        }
    );
}

void SPIDEProvider::cancelRequest()
{
    if (!currentReply) {
        return;
    }

    QNetworkReply *reply =
        currentReply;

    currentReply = nullptr;

    reply->abort();
    reply->deleteLater();
}