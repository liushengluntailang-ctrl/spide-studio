#include "Terminal.h"
#include <QVBoxLayout>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QProcess>
Terminal::Terminal(QWidget*p):QWidget(p){auto*l=new QVBoxLayout(this);l->setContentsMargins(14,8,14,10);out=new QPlainTextEdit;out->setReadOnly(true);in=new QLineEdit;in->setPlaceholderText("$ Enter command...");proc=new QProcess(this);proc->setProcessChannelMode(QProcess::MergedChannels);l->addWidget(out);l->addWidget(in);connect(in,&QLineEdit::returnPressed,this,[this](){auto c=in->text().trimmed();if(c.isEmpty())return;out->appendPlainText("$ "+c);in->clear();
#ifdef Q_OS_WIN
proc->start("cmd.exe",{"/C",c});
#else
proc->start("/bin/sh",{"-c",c});
#endif
});connect(proc,&QProcess::readyRead,this,[this](){out->appendPlainText(QString::fromLocal8Bit(proc->readAll()));});}
