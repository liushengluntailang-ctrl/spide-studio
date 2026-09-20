#pragma once

#include <QDialog>

class QComboBox;
class QLineEdit;
class QSpinBox;

class Settings : public QDialog
{
    Q_OBJECT
public:
    explicit Settings(QWidget *parent = nullptr);

    QString serverUrl() const;
    QString token() const;
    QString model() const;
    int fontSize() const;
    QString theme() const;
    QString shell() const;

signals:
    void settingsChanged();

private slots:
    void save();

private:
    QLineEdit *serverUrlEdit;
    QLineEdit *tokenEdit;
    QComboBox *modelCombo;
    QSpinBox *fontSizeSpin;
    QComboBox *themeCombo;
    QLineEdit *shellEdit;
};
