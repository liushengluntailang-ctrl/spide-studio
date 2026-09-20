#include "AIChat.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>
AIChat::AIChat(QWidget*p):QWidget(p){n=new QNetworkAccessManager(this);auto*l=new QVBoxLayout(this);l->setContentsMargins(14,14,14,14);auto*t=new QLabel("AI CHAT");t->setObjectName("panelTitle");l->addWidget(t);h=new QTextEdit;h->setReadOnly(true);l->addWidget(h);auto*r=new QHBoxLayout;i=new QLineEdit;i->setPlaceholderText("Ask Spide...");b=new QPushButton("Send");b->setObjectName("primaryButton");r->addWidget(i);r->addWidget(b);l->addLayout(r);connect(b,&QPushButton::clicked,this,&AIChat::send);connect(i,&QLineEdit::returnPressed,this,&AIChat::send);}
void AIChat::send(){auto p=i->text().trimmed();if(p.isEmpty())return;h->append("<b>You</b><br>"+p.toHtmlEscaped()+"<br>");i->clear();QNetworkRequest q(QUrl("http://127.0.0.1:8000/generate"));q.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");QJsonObject o{{"prompt",p},{"engine","speed03"}};auto*r=n->post(q,QJsonDocument(o).toJson());connect(r,&QNetworkReply::finished,this,[this,r](){if(r->error()!=QNetworkReply::NoError)h->append("<b>Spide</b><br>Server unavailable.<br>");else{auto o=QJsonDocument::fromJson(r->readAll()).object();h->append("<b>Spide</b><br>"+o.value("response").toString().toHtmlEscaped()+"<br>");}r->deleteLater();});}
