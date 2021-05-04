#include "./headers/category.h"

CategoryModel::CategoryModel(){

}
CategoryModel::~CategoryModel(){

}
void CategoryModel::setCategoryId(int categoryId){
    this->categoryId=categoryId;
}

int CategoryModel::getCategoryId(){
    return this->categoryId;
}
void CategoryModel::setParentId(int parentId){
    this->parentId=parentId;
}

int CategoryModel::getParentId(){
    return this->parentId;
}

void CategoryModel::setParentName(QString parentName){
    this->parentName=parentName;
}

QString CategoryModel::getParentName(){
    return this->parentName;
}

void CategoryModel::setUserId(int userId){
    this->userId=userId;
}

int CategoryModel::getUserId(){
    return this->userId;
}

void CategoryModel::setName(QString name){
    this->name=name;
}

QString CategoryModel::getName(){
    return this->name;
}



