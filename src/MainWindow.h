#pragma once
#include <QMainWindow>
class Explorer;class QTabWidget;class AIChat;class Terminal;class QLabel;class QToolButton;
class MainWindow:public QMainWindow{Q_OBJECT public:explicit MainWindow(QWidget*p=nullptr);private:Explorer*e;QTabWidget*t;AIChat*a;Terminal*term;QToolButton*ai;void style();};
