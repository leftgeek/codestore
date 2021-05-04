#ifndef DATABASE_H
#define DATABASE_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class Database{
private:
    static QSqlDatabase dbConnect;//数据库连接
    static QString dbType;//数据库类型
    static QString dbName;//数据库名
    static QString hostName;//
    static int port;//端口号
    static QString username;//用户名
    static QString password;//密码
public:
    Database();
    ~Database();
    static void initDb();
    bool connectDb();
    QSqlQuery queryDb(QString sql);
    void closeDb();
};
#endif // DATABASE_H
