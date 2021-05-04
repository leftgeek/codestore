#include "./headers/modifyPasswordWidget.h"
#include "./headers/user.h"
ModifyPasswordWidget::ModifyPasswordWidget(QWidget* parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

ModifyPasswordWidget::~ModifyPasswordWidget(){

}

void ModifyPasswordWidget::setupWidgets(){
    this->setWindowTitle("Modify password");
    this->usernameLabel=new QLabel("Username:");
    this->oldPasswordLabel=new QLabel("Old password:");
    this->newPasswordLabel=new QLabel("New password:");
    this->confirmPasswordLabel=new QLabel("Confirm password:");
    this->messageLabel=new QLabel("Please enter your new password");
    this->usernameLineEdit=new QLineEdit();
    this->oldPasswordLineEdit=new QLineEdit();
    this->oldPasswordLineEdit->setEchoMode(QLineEdit::Password);
    this->newPasswordLineEdit=new QLineEdit();
    this->newPasswordLineEdit->setEchoMode(QLineEdit::Password);
    this->confirmPasswordLineEdit=new QLineEdit();
    this->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    this->confirmButton=new QPushButton("Confirm");
    this->cancelButton=new QPushButton("Cancel");

}

void ModifyPasswordWidget::setupLayouts(){
    QFormLayout *formLayout1 = new QFormLayout();
    formLayout1->addRow(this->usernameLabel,this->usernameLineEdit);
    formLayout1->addRow(this->oldPasswordLabel,this->oldPasswordLineEdit);
    formLayout1->addRow(this->newPasswordLabel,this->newPasswordLineEdit);
    formLayout1->addRow(this->confirmPasswordLabel,this->confirmPasswordLineEdit);

    QGridLayout* gridLayout=new QGridLayout();
    gridLayout->addWidget(this->confirmButton,0,0,1,1);
    gridLayout->addWidget(this->cancelButton,0,1,1,1);
    formLayout1->addRow(gridLayout);

    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addLayout(formLayout1);
    vLayout->addWidget(this->messageLabel);
    this->setLayout(vLayout);
}

void ModifyPasswordWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void ModifyPasswordWidget::onConfirm(){
    QString username=this->usernameLineEdit->text();
    QString oldPassword=this->oldPasswordLineEdit->text();
    QString newPassword=this->newPasswordLineEdit->text();
    QString confirmPassword=this->confirmPasswordLineEdit->text();
    if(newPassword==confirmPassword){
        UserModel* userModel=new UserModel();
        userModel->setUsername(username);
        userModel->setPassword(oldPassword);

        UserControl uc;
        if(uc.checkLogin(userModel)){
            userModel->setPassword(newPassword);
            if(uc.modifyPassword(userModel)){
                this->showMessage("modify successful");
                this->accept();
            }else{
                this->showMessage("modify failed");
            }
        }else{
            this->showMessage("username or password wrong");
        }
        delete(userModel);
    }else{
        this->showMessage("password is wrong");
    }
}

void ModifyPasswordWidget::onCancel(){
    this->close();
}

void ModifyPasswordWidget::showMessage(QString message){
    this->messageLabel->setText(message);
}


