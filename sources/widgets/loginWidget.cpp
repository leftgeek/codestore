#include "./headers/loginWidget.h"
#include "./headers/user.h"
#include "./headers/sync.h"
LoginWidget::LoginWidget(QWidget* parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

LoginWidget::~LoginWidget(){

}

void LoginWidget::setupWidgets(){
    this->setWindowTitle("Login");
    this->usernameLabel=new QLabel("Username:");
    this->passwordLabel=new QLabel("Password:");
    this->messageLabel=new QLabel("Please enter your username and password");
    this->usernameLineEdit=new QLineEdit();
    this->passwordLineEdit=new QLineEdit();
    this->passwordLineEdit->setEchoMode(QLineEdit::Password);
    this->confirmButton=new QPushButton("Login");
    this->cancelButton=new QPushButton("Cancel");

}

void LoginWidget::setupLayouts(){
    QFormLayout *formLayout1 = new QFormLayout();
    formLayout1->addRow(this->usernameLabel,this->usernameLineEdit);
    formLayout1->addRow(this->passwordLabel,this->passwordLineEdit);

    QGridLayout* gridLayout=new QGridLayout();
    gridLayout->addWidget(this->confirmButton,0,0,1,1);
    gridLayout->addWidget(this->cancelButton,0,1,1,1);
    formLayout1->addRow(gridLayout);

    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addLayout(formLayout1);
    vLayout->addWidget(this->messageLabel);
    this->setLayout(vLayout);
}

void LoginWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void LoginWidget::onConfirm(){
    QString username=this->usernameLineEdit->text();
    QString password=this->passwordLineEdit->text();
    UserModel* userModel=new UserModel();
    userModel->setUsername(username);
    userModel->setPassword(password);

    UserControl uc;
    if(uc.checkLogin(userModel)){
        Sync* sync=Sync::getSync();
        sync->setUser(userModel);
        this->showMessage("login successful");
        this->accept();
    }else{
        this->showMessage("username or password wrong");
    }
    delete(userModel);
}

void LoginWidget::onCancel(){
    this->close();
}

void LoginWidget::showMessage(QString message){
    this->messageLabel->setText(message);
}

