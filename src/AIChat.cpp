#include "AIChat.h"
#include "ai/IAIProvider.h"

#include <QHBoxLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

AIChat::AIChat(QWidget *parent)
    : QWidget(parent),
      messages(new QPlainTextEdit(this)),
      input(new QLineEdit(this))
{
    messages->setReadOnly(true);
    messages->setPlaceholderText("SPIDE AI conversation");

    input->setPlaceholderText("Ask SPIDE AI...");

    auto *send = new QPushButton("Send");
    auto *stop = new QPushButton("Stop");

    auto *controls = new QHBoxLayout;
    controls->addWidget(input);
    controls->addWidget(send);
    controls->addWidget(stop);

    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->addWidget(messages);
    layout->addLayout(controls);

    connect(send, &QPushButton::clicked, this, &AIChat::sendMessage);
    connect(input, &QLineEdit::returnPressed, this, &AIChat::sendMessage);
    connect(stop, &QPushButton::clicked, this, [this] {
        if (provider) {
            provider->cancelRequest();
            messages->appendPlainText("[Request stopped]");
        }
    });
}

void AIChat::setProvider(IAIProvider *value)
{
    provider = value;
    if (!provider) return;

    connect(provider, &IAIProvider::responseReady, this,
            [this](const QString &response) {
                messages->appendPlainText("SPIDE AI:\n" + response);
            });

    connect(provider, &IAIProvider::errorOccurred, this,
            [this](const QString &error) {
                messages->appendPlainText("SPIDE AI error: " + error);
            });
}

void AIChat::setContext(const QString &path, const QString &text, const QString &selected)
{
    filePath = path;
    contents = text;
    selection = selected;
}

void AIChat::sendMessage()
{
    const QString message = input->text().trimmed();
    if (message.isEmpty() || !provider) return;

    messages->appendPlainText("You:\n" + message);
    input->clear();

    QString context;

    if (!filePath.isEmpty()) {
        context = QString("File: %1\n%2")
                      .arg(filePath, selection.isEmpty() ? contents : selection);
    }

    provider->sendMessage(message, context);
}
