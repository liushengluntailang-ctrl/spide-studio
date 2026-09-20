#pragma once
#include <QWidget>
class QTextEdit;class QLineEdit;class QPushButton;class QNetworkAccessManager;
class AIChat:public QWidget{Q_OBJECT public:explicit AIChat(QWidget*p=nullptr);private slots:void send();private:QTextEdit*h;QLineEdit*i;QPushButton*b;QNetworkAccessManager*n;};
