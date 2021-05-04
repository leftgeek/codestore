#include "./headers/registerWidget.h"
#include "./headers/user.h"
RegisterWidget::RegisterWidget(QWidget* parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

RegisterWidget::~RegisterWidget(){

}

void RegisterWidget::setupWidgets(){
    this->setWindowTitle("Register");
    this->usernameLabel=new QLabel("Username:");
    this->passwordLabel=new QLabel("Password:");
    this->confirmPasswordLabel=new QLabel("Confirm password:");
    this->messageLabel=new QLabel("Please enter your username and password");
    this->emailLabel=new QLabel("Email:");
    this->usernameLineEdit=new QLineEdit();
    this->passwordLineEdit=new QLineEdit();
    this->passwordLineEdit->setEchoMode(QLineEdit::Password);
    this->confirmPasswordLineEdit=new QLineEdit();
    this->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    this->emailLineEdit=new QLineEdit();
    this->confirmButton=new QPushButton("Register");
    this->cancelButton=new QPushButton("Cancel");

}

void RegisterWidget::setupLayouts(){
    QFormLayout *formLayout1 = new QFormLayout();
    formLayout1->addRow(this->usernameLabel,this->usernameLineEdit);
    formLayout1->addRow(this->passwordLabel,this->passwordLineEdit);
    formLayout1->addRow(this->confirmPasswordLabel,this->confirmPasswordLineEdit);
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

void RegisterWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void RegisterWidget::onConfirm(){
    QString username=this->usernameLineEdit->text();
    QString password=this->passwordLineEdit->text();
    QString confirmPassword=this->confirmPasswordLineEdit->text();
    QString email=this->emailLineEdit->text();
    if(password==confirmPassword){
        UserModel* userModel=new UserModel();
        userModel->setUsername(username);
        userModel->setPassword(password);
        userModel->setEmail(email);

        UserControl uc;
        if(uc.addUser(userModel)){
            this->showMessage("register successful");
            this->accept();
        }else{
            this->showMessage("register fail");
        }
        delete(userModel);
    }else{
        this->showMessage("password is wrong");
    }

}

void RegisterWidget::onCancel(){
    this->close();
}

void RegisterWidget::showMessage(QString message){
    this->messageLabel->setText(message);
}



