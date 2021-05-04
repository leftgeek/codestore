#include "./headers/findPasswordWidget.h"
#include "./headers/user.h"
FindPasswordWidget::FindPasswordWidget(QWidget* parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

FindPasswordWidget::~FindPasswordWidget(){

}

void FindPasswordWidget::setupWidgets(){
    this->setWindowTitle("Find password");
    this->emailLabel=new QLabel("Email:");
    this->messageLabel=new QLabel("Please enter your Email address");
    this->emailLineEdit=new QLineEdit();
    this->confirmButton=new QPushButton("Confirm");
    this->cancelButton=new QPushButton("Cancel");

}

void FindPasswordWidget::setupLayouts(){
    QFormLayout *formLayout1 = new QFormLayout();
    formLayout1->addRow(this->emailLabel,this->emailLineEdit);

    QGridLayout* gridLayout=new QGridLayout();
    gridLayout->addWidget(this->confirmButton,0,0,1,1);
    gridLayout->addWidget(this->cancelButton,0,1,1,1);
    formLayout1->addRow(gridLayout);

    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addLayout(formLayout1);
    vLayout->addWidget(this->messageLabel);
    this->setLayout(vLayout);
}

void FindPasswordWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void FindPasswordWidget::onConfirm(){
    QString email=this->emailLineEdit->text();
    UserControl* uc=new UserControl();
    if(uc->sendEmail(email)){
        this->showMessage("Email is send successful");
        this->accept();
    }else{
        this->showMessage("Email is send fail");
    }
    delete(uc);
}

void FindPasswordWidget::onCancel(){
    this->close();
}

void FindPasswordWidget::showMessage(QString message){
    this->messageLabel->setText(message);
}


