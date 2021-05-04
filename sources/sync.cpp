#include "./headers/sync.h"
#include "./headers/logTree.h"
#include "./headers/codeTreeWidget.h"
Sync* Sync::sync=NULL;
Sync::Sync(){
    this->userModel=new UserModel();
}

Sync::~Sync(){

}

Sync* Sync::getSync(){
    if(sync==NULL){
        sync=new Sync();
    }
    return sync;
}

void Sync::setUser(UserModel *userModel){
    this->userModel=userModel;
}

UserModel* Sync::getUser(){
    return this->userModel;
}

void Sync::syncCode(){
    if(this->isLogin()){
        int userId = this->userModel->getUserId();

        //section1
        LogTree* logTree=LogTree::getLogTree();
        logTree->syncLog(userId);

        //section2
        CodeTree* codeTree=CodeTree::getCodeTree();
        codeTree->syncCode(userId);

        //section3
        CodeTreeWidget* codeTreeWidget=CodeTreeWidget::getCodeTreeWidget();
        codeTreeWidget->downloadCategory(userId);
        codeTreeWidget->downloadCode(userId);
    }
}

bool Sync::isLogin(){
    bool result=false;
    UserControl uc;
    if(this->userModel!=NULL&&uc.checkLogin(this->userModel)){
        result=true;
    }
    return result;
}

bool Sync::autoLogin(){
    QSettings settings("config/config.ini",QSettings::IniFormat);
    QString username=settings.value("user/username","").toString();
    QString password=settings.value("user/password","").toString();
    this->userModel=new UserModel();
    this->userModel->setUsername(username);
    this->userModel->setPassword(password);
    bool result=this->isLogin();
    return result;
}

