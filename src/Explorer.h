#pragma once
#include <QWidget>
class QTreeView; class QFileSystemModel;
class Explorer:public QWidget{Q_OBJECT public:explicit Explorer(QWidget*p=nullptr);signals:void fileActivated(const QString&);private:QFileSystemModel*m;QTreeView*t;};
