#include "Editor.h"
#include <QFile>
#include <QTextStream>
#include <QFontDatabase>
Editor::Editor(QWidget*p):QPlainTextEdit(p){setObjectName("editor");setLineWrapMode(NoWrap);setFont(QFontDatabase::systemFont(QFontDatabase::FixedFont));setPlaceholderText("Start writing code...");}
void Editor::openFile(const QString&path){QFile f(path);if(f.open(QIODevice::ReadOnly|QIODevice::Text)){QTextStream s(&f);setPlainText(s.readAll());}}
