#include "./headers/user.h"

UserModel::UserModel(){

}
UserModel::~UserModel(){

}
void UserModel::setUserId(int userId){
    this->userId=userId;
}

int UserModel::getUserId(){
    return this->userId;
}

void UserModel::setUsername(QString username){
    this->username=username;
}

QString UserModel::getUsername(){
    return this->username;
}

void UserModel::setPassword(QString password){
    this->password=password;
}

QString UserModel::getPassword(){
    return this->password;
}

void UserModel::setEmail(QString email){
    this->email=email;
}

QString UserModel::getEmail(){
    return this->email;
}
