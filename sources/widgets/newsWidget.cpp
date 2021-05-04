#include "./headers/newsWidget.h"
NewsWidget::NewsWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

NewsWidget::~NewsWidget(){

}

void NewsWidget::setupWidgets(){
    this->fileLabel=new QLabel("Shared Files");
    this->fileLabel->setFont(QFont("Ubuntu",18,QFont::Bold));
    this->fileListWidget=new QListWidget();
    this->fileListWidget->setAlternatingRowColors(true);
}

void NewsWidget::setupLayouts(){
    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addWidget(this->fileLabel);
    vLayout->addWidget(this->fileListWidget);

    this->setLayout(vLayout);
}

void NewsWidget::setupActions(){

}


