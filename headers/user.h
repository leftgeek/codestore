#ifndef USER_H
#define USER_H
#include <QtGui>
#include "./headers/database.h"
class UserModel{
private:
    int userId;
    QString username;
    QString password;
    QString email;
public:
    UserModel();
    ~UserModel();
    void setUserId(int userId);
    int getUserId();
    void setUsername(QString username);
    QString getUsername();
    void setPassword(QString password);
    QString getPassword();
    void setEmail(QString email);
    QString getEmail();

};
class UserControl:public Database{
public:
    UserControl();
    ~UserControl();
    bool checkLogin(UserModel* userModel);
    bool addUser(UserModel* userModel);
    bool modifyPassword(UserModel* userModel);
    bool sendEmail(QString email);
};
#endif // USER_H
