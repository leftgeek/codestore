#include "./headers/personalCenterWidget.h"
#include "./headers/registerWidget.h"
#include "./headers/loginWidget.h"
#include "./headers/modifyPasswordWidget.h"
#include "./headers/findPasswordWidget.h"
PersonalCenterWidget::PersonalCenterWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();

}

PersonalCenterWidget::~PersonalCenterWidget(){

}

void PersonalCenterWidget::setupWidgets(){
    this->fileLabel=new QLabel("My Files");
    this->fileLabel->setFont(QFont("Ubuntu",18,QFont::Bold));
    this->fileListWidget=new QListWidget();
    this->fileListWidget->setAlternatingRowColors(true);

    this->registerButton=new QPushButton("Register");
    this->loginButton=new QPushButton("Login");
    this->modifyPasswordButton=new QPushButton("Modify password");
    this->findPasswordButton=new QPushButton("Find password");
}

void PersonalCenterWidget::setupLayouts(){
    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addWidget(this->fileLabel);
    vLayout->addWidget(this->fileListWidget);

    QGridLayout* gLayout=new QGridLayout();
    gLayout->addWidget(this->registerButton,0,0,1,1);
    gLayout->addWidget(this->loginButton,0,1,1,1);
    gLayout->addWidget(this->modifyPasswordButton,1,0,1,1);
    gLayout->addWidget(this->findPasswordButton,1,1,1,1);

    vLayout->addLayout(gLayout);
    this->setLayout(vLayout);
}

void PersonalCenterWidget::setupActions(){
    QObject::connect(this->registerButton,SIGNAL(clicked()),this,SLOT(onRegister()));
    QObject::connect(this->loginButton,SIGNAL(clicked()),this,SLOT(onLogin()));
    QObject::connect(this->modifyPasswordButton,SIGNAL(clicked()),this,SLOT(onModifyPassword()));
    QObject::connect(this->findPasswordButton,SIGNAL(clicked()),this,SLOT(onFindPassword()));
}

void PersonalCenterWidget::onRegister(){
    RegisterWidget registerWidget;
    if(registerWidget.exec()==QDialog::Accepted){

    }
}

void PersonalCenterWidget::onLogin(){
    LoginWidget loginWidget;
    if(loginWidget.exec()==QDialog::Accepted){
        this->registerButton->setEnabled(false);
        this->loginButton->setEnabled(false);
    }
}

void PersonalCenterWidget::onModifyPassword(){
    ModifyPasswordWidget modifyPasswordWidget;
    if(modifyPasswordWidget.exec()==QDialog::Accepted){

    }
}

void PersonalCenterWidget::onFindPassword(){
    FindPasswordWidget findPasswordWidget;
    if(findPasswordWidget.exec()==QDialog::Accepted){

    }
}















