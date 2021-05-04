#include "./headers/code.h"

CodeModel::CodeModel(){

}
CodeModel::~CodeModel(){

}
void CodeModel::setCodeId(int codeId){
    this->codeId=codeId;
}

int CodeModel::getCodeId(){
    return this->codeId;
}
void CodeModel::setCategoryId(int categoryId){
    this->categoryId=categoryId;
}

int CodeModel::getCategoryId(){
    return this->categoryId;
}

void CodeModel::setName(QString name){
    this->name=name;
}

QString CodeModel::getName(){
    return this->name;
}

void CodeModel::setCategoryName(QString categoryName){
       this->categoryName=categoryName;
}

QString CodeModel::getCategoryName(){
    return this->categoryName;
}


void CodeModel::setDescription(QString description){
    this->description=description;
}

QString CodeModel::getDescription(){
    return this->description;
}

void CodeModel::setContent(QString content){
    this->content=content;
}

QString CodeModel::getContent(){
    return this->content;
}

void CodeModel::setShareStatus(int shareStatus){
    this->shareStatus=shareStatus;
}
int CodeModel::getShareStatus(){
    return this->shareStatus;
}




