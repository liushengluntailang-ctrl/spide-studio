#include "MainWindow.h"
#include "Explorer.h"
#include "Editor.h"
#include "AIChat.h"
#include "Terminal.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QToolButton>
#include <QTabWidget>
#include <QSplitter>
#include <QStatusBar>
#include <QMenuBar>
#include <QDir>
MainWindow::MainWindow(QWidget*p):QMainWindow(p){resize(1440,900);setWindowTitle("Spide Studio");style();auto*c=new QWidget;setCentralWidget(c);auto*root=new QVBoxLayout(c);root->setContentsMargins(0,0,0,0);root->setSpacing(0);
auto*top=new QWidget;top->setObjectName("top");top->setFixedHeight(54);auto*tl=new QHBoxLayout(top);tl->setContentsMargins(18,0,18,0);auto*logo=new QLabel("Spide");logo->setObjectName("logo");tl->addWidget(logo);tl->addStretch();ai=new QToolButton;ai->setText("AI  ON");ai->setCheckable(true);ai->setChecked(true);ai->setObjectName("ai");tl->addWidget(ai);auto*set=new QPushButton("Settings");set->setObjectName("flat");tl->addWidget(set);root->addWidget(top);
auto*sp=new QSplitter(Qt::Horizontal);e=new Explorer;sp->addWidget(e);auto*mid=new QWidget;auto*ml=new QVBoxLayout(mid);ml->setContentsMargins(0,0,0,0);ml->setSpacing(0);t=new QTabWidget;t->setTabsClosable(true);auto*w=new Editor;w->setPlainText("// Welcome to Spide Studio 0.2\n// Fast. Native. Student-friendly.\n\nStart writing code or ask Spide AI.");t->addTab(w,"Welcome");ml->addWidget(t);term=new Terminal;term->setMinimumHeight(180);ml->addWidget(term);sp->addWidget(mid);a=new AIChat;sp->addWidget(a);sp->setStretchFactor(0,1);sp->setStretchFactor(1,4);sp->setStretchFactor(2,2);root->addWidget(sp,1);
connect(e,&Explorer::fileActivated,this,[this](const QString&p){auto*x=new Editor;x->openFile(p);t->addTab(x,QFileInfo(p).fileName());t->setCurrentWidget(x);});connect(t,&QTabWidget::tabCloseRequested,this,[this](int i){if(i>0)t->removeTab(i);});statusBar()->showMessage("Ready");auto*s=new QLabel("● Connected");s->setObjectName("good");statusBar()->addPermanentWidget(s);connect(ai,&QToolButton::clicked,this,[this](){a->setEnabled(ai->isChecked());ai->setText(ai->isChecked()?"AI  ON":"AI OFF");});}
void MainWindow::style(){qApp->setStyleSheet(R"(
QWidget{font-family:"Segoe UI";font-size:13px;color:#20242a;background:#fff}
#top{border-bottom:1px solid #e7ebf0}#logo{color:#1677ff;font-size:22px;font-weight:800}
#panelTitle{color:#7a8491;font-size:11px;font-weight:700}
QTreeView{border:0;background:#fbfcfe}QTreeView::item{padding:6px;border-radius:6px}QTreeView::item:hover{background:#eef5ff}QTreeView::item:selected{background:#e4f0ff;color:#1268db}
QTabWidget::pane{border:0}QTabBar::tab{padding:9px 16px;background:#f7f9fb;border-right:1px solid #e7ebf0;color:#68717d}QTabBar::tab:selected{background:#fff;color:#1677ff;border-top:2px solid #1677ff}
#editor{border:0;padding:16px}#aiChat{background:#fbfcfe;border-left:1px solid #e7ebf0}#aiChat QTextEdit{border:1px solid #e7ebf0;border-radius:8px}#aiChat QLineEdit{border:1px solid #dce2e8;border-radius:8px;padding:9px}
#primaryButton{background:#1677ff;color:white;border:0;border-radius:7px;padding:8px 14px;font-weight:700}#flat{background:transparent;border:0;padding:7px 10px;color:#5d6672}#ai{background:#eef6ff;color:#1677ff;border:1px solid #d8eaff;border-radius:7px;padding:7px 12px}
#terminal{background:#111827;border-top:1px solid #e7ebf0}#terminal QPlainTextEdit{background:#111827;color:#d7e0ea;border:0}#terminal QLineEdit{background:#182131;color:#e8eef5;border:1px solid #263246;border-radius:6px;padding:7px}
QStatusBar{border-top:1px solid #e7ebf0;color:#7a8491}#good{color:#1aa66a;padding-right:10px}QSplitter::handle{background:#e7ebf0}
)");}
