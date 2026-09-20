#pragma once
#include <QPlainTextEdit>
class Editor:public QPlainTextEdit{Q_OBJECT public:explicit Editor(QWidget*p=nullptr);void openFile(const QString&);};
