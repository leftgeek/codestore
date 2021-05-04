#include "./headers/helpWidget.h"
#include <QVBoxLayout>
HelpWidget::HelpWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
}

HelpWidget::~HelpWidget(){

}

void HelpWidget::setupWidgets(){
    this->setAccessibleName("help");
    this->setAccessibleDescription("html");
    this->webView=new QWebView();
    webView->load(QUrl("config/help.html"));

    QVBoxLayout* vBoxLayout=new QVBoxLayout();
    vBoxLayout->addWidget(this->webView);
    this->setLayout(vBoxLayout);
}
