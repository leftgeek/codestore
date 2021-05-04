#include "./headers/user.h"
#include "./headers/category.h"
#include "./headers/sendEmail.h"
UserControl::UserControl():Database(){

}

UserControl::~UserControl(){

}

bool UserControl::checkLogin(UserModel* userModel){
    bool result=false;
    if(this->connectDb()){
        QString sql = "select * from users where username='"+userModel->getUsername()+"'";
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            QString pswd=query.value(2).toString();
            if(pswd==userModel->getPassword()){
                userModel->setUserId(query.value(0).toInt());
                result=true;
            }
        }
        this->closeDb();
    }
    return result;
}

bool UserControl::addUser(UserModel* userModel) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "select max(user_id) from users";
        QSqlQuery query = this->queryDb(sql);
        int id=0;
        if(query.next()){
            id=query.value(0).toInt();
        }
        id++;
        userModel->setUserId(id);
        sql = "insert into users values("+QString::number(id)+",'"+ userModel->getUsername()+ "','" + userModel->getPassword()
                        + "','" + userModel->getEmail() +"')";
        this->queryDb(sql);
        this->closeDb();
        //为新用户建立一个总分类categories
        CategoryModel* cm=new CategoryModel();
        cm->setParentId(0);//NULL
        cm->setUserId(id);
        cm->setName("categories");

        CategoryControl* cc=new CategoryControl();
        result=cc->addCategory(cm);
        delete(cm);
        delete(cc);
    }
    return result;
}

bool UserControl::modifyPassword(UserModel* userModel) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "update users set password='" + userModel->getPassword() +"' where user_id="+QString::number(userModel->getUserId());
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

bool UserControl::sendEmail(QString email) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "select * from users where email='"+email+"'";
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            QString username=query.value(1).toString();
            QString password=query.value(2).toString();
            QString email=query.value(3).toString();

        }
        result=true;
        this->closeDb();
    }
    return result;
}
