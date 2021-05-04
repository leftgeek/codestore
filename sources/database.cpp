#include "./headers/database.h"
#include <QtGui>
#include <QSettings>

QSqlDatabase Database::dbConnect;
QString Database::dbType;
QString Database::dbName;
QString Database::hostName;
int Database::port;
QString Database::username;
QString Database::password;

Database::Database(){
    if(!dbConnect.contains()){
        this->initDb();
    }
}

Database::~Database(){

}

void Database::initDb(){

    dbType="QMYSQL";
    dbName="codestore";
    hostName="localhost";
    port=3306;
    username="root";
    password="yuya2011";

    dbConnect = QSqlDatabase::addDatabase(dbType);
    dbConnect.setHostName(hostName);
    dbConnect.setPort(port);
    dbConnect.setDatabaseName(dbName);
    dbConnect.setUserName(username);
    dbConnect.setPassword(password);

}

bool Database::connectDb(){
    bool result;
    if (dbConnect.open()) {
        result=true;
    }else{
        result=false;
    }
    return result;
}

QSqlQuery Database::queryDb(QString sql){
    QSqlQuery query(dbConnect);
    query.exec(sql);
    return query;
}

void Database::closeDb() {
    dbConnect.close();
}


