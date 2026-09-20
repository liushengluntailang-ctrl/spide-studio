#include "Settings.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QSettings>
#include <QSpinBox>
#include <QVBoxLayout>

Settings::Settings(QWidget *parent)
    : QDialog(parent),
      serverUrlEdit(new QLineEdit),
      tokenEdit(new QLineEdit),
      modelCombo(new QComboBox),
      fontSizeSpin(new QSpinBox),
      themeCombo(new QComboBox),
      shellEdit(new QLineEdit)
{
    setWindowTitle("SPIDE Studio Settings");
    setModal(true);
    resize(500, 330);

    modelCombo->addItems({
        "spide-speed-0.3",
        "spide-null-0.6",
        "spide-null-pro-0.5"
    });

    fontSizeSpin->setRange(8, 32);
    themeCombo->addItems({"Dark", "Light"});

    serverUrlEdit->setPlaceholderText("http://localhost:8000/v1/chat/completions");
    tokenEdit->setPlaceholderText("Optional");
    tokenEdit->setEchoMode(QLineEdit::Password);
    shellEdit->setPlaceholderText("/bin/bash");

    QSettings settings;

    serverUrlEdit->setText(
        settings.value(
            "spide/serverUrl",
            "http://localhost:8000/v1/chat/completions"
        ).toString()
    );

    tokenEdit->setText(settings.value("spide/token").toString());

    modelCombo->setCurrentText(
        settings.value("spide/model", "spide-speed-0.3").toString()
    );

    fontSizeSpin->setValue(
        settings.value("editor/fontSize", 12).toInt()
    );

    themeCombo->setCurrentText(
        settings.value("ui/theme", "Dark").toString()
    );

    shellEdit->setText(
        settings.value("terminal/shell", "/bin/bash").toString()
    );

    auto *form = new QFormLayout;
    form->addRow("SPIDE Server URL", serverUrlEdit);
    form->addRow("SPIDE Token", tokenEdit);
    form->addRow("SPIDE Model", modelCombo);
    form->addRow("Font Size", fontSizeSpin);
    form->addRow("Theme", themeCombo);
    form->addRow("Terminal Shell", shellEdit);

    auto *saveButton = new QPushButton("Save");

    auto *layout = new QVBoxLayout(this);
    layout->addLayout(form);
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked,
            this, &Settings::save);
}

QString Settings::serverUrl() const
{
    return serverUrlEdit->text().trimmed();
}

QString Settings::token() const
{
    return tokenEdit->text();
}

QString Settings::model() const
{
    return modelCombo->currentText();
}

int Settings::fontSize() const
{
    return fontSizeSpin->value();
}

QString Settings::theme() const
{
    return themeCombo->currentText();
}

QString Settings::shell() const
{
    return shellEdit->text().trimmed();
}

void Settings::save()
{
    QSettings settings;

    settings.setValue("spide/serverUrl", serverUrl());
    settings.setValue("spide/token", token());
    settings.setValue("spide/model", model());
    settings.setValue("editor/fontSize", fontSize());
    settings.setValue("ui/theme", theme());
    settings.setValue("terminal/shell", shell());

    emit settingsChanged();
    accept();
}
