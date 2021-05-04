#ifndef CODE_H
#define CODE_H
#include <QtGui>
#include <QTableWidget>
#include "./headers/database.h"
class CodeModel{
private:
    int codeId;//分类号
    int categoryId;//父分类号
    QString name;//名称
    QString categoryName;//
    QString description;//
    QString content;//
    int shareStatus;//
public:
    CodeModel();
    ~CodeModel();
    void setCodeId(int codeId);
    int getCodeId();
    void setCategoryId(int categoryId);
    int getCategoryId();
    void setName(QString name);
    QString getName();
    void setCategoryName(QString categoryName);
    QString getCategoryName();
    void setDescription(QString description);
    QString getDescription();
    void setContent(QString content);
    QString getContent();
    void setShareStatus(int shareStatus);
    int getShareStatus();

};
class CodeControl:public Database{

public:
    CodeControl();
    ~CodeControl();
    CodeModel* getCode(int codeId);
    CodeModel* getCode(QString name,int userId);
    QList<CodeModel*> getAllCodes(int userId);
    QList<CodeModel*> searchAllCodes(QString keywords,int pageNow);
    bool addCode(CodeModel* codeModel);
    bool editCode(CodeModel* codeModel);
    bool deleteCode(int codeId,int userId);
};
#endif // CODE_H

