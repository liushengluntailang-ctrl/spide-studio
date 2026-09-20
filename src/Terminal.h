#pragma once
#include <QWidget>
class QPlainTextEdit;class QLineEdit;class QProcess;
class Terminal:public QWidget{Q_OBJECT public:explicit Terminal(QWidget*p=nullptr);private:QPlainTextEdit*out;QLineEdit*in;QProcess*proc;};
