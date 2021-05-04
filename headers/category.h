#ifndef CATEGORY_H
#define CATEGORY_H
#include <QtGui>
#include <QTableWidget>
#include "./headers/database.h"
class CategoryModel{
private:
    int categoryId;//分类号
    int parentId;//父分类号
    QString parentName;//parent category name
    int userId;//
    QString name;//名称
public:
    CategoryModel();
    ~CategoryModel();
    void setCategoryId(int categoryId);
    int getCategoryId();
    void setParentId(int parentId);
    int getParentId();
    void setParentName(QString parentName);
    QString getParentName();
    void setUserId(int userId);
    int getUserId();
    void setName(QString name);
    QString getName();
};
class CategoryControl:public Database{

public:
    CategoryControl();
    ~CategoryControl();
    CategoryModel* getCategory(int categoryId);
    CategoryModel* getCategory(QString name,int userId);
    QList<CategoryModel*> getAllCategories(int userId);
    bool addCategory(CategoryModel* categoryModel);
    bool editCategory(CategoryModel* categoryModel);
    bool deleteCategory(int categoryId,int userId);
};

#endif // CATEGORY_H
