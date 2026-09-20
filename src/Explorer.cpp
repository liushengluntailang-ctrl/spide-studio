#include "Explorer.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QTreeView>
#include <QFileSystemModel>
#include <QDir>
Explorer::Explorer(QWidget*p):QWidget(p){auto*l=new QVBoxLayout(this);l->setContentsMargins(14,14,10,10);auto*h=new QLabel("EXPLORER");h->setObjectName("panelTitle");l->addWidget(h);m=new QFileSystemModel(this);m->setRootPath(QDir::homePath());t=new QTreeView; t->setModel(m);t->setRootIndex(m->index(QDir::homePath()));t->setHeaderHidden(true);for(int i=1;i<4;i++)t->hideColumn(i);l->addWidget(t);connect(t,&QTreeView::doubleClicked,this,[this](const QModelIndex&i){if(!m->isDir(i))emit fileActivated(m->filePath(i));});}
