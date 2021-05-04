#include "./headers/category.h"
CategoryControl::CategoryControl():Database(){

}

CategoryControl::~CategoryControl(){

}

CategoryModel* CategoryControl::getCategory(int categoryId){
    CategoryModel* cm=NULL;
    if(this->connectDb()){
        QString sql="select * from categories where category_id="+QString::number(categoryId);
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            cm=new CategoryModel();
            cm->setCategoryId(categoryId);
            cm->setParentId(query.value(1).toInt());
            cm->setUserId(query.value(2).toInt());
            cm->setName(query.value(3).toString());
        }
        this->closeDb();
    }
    return cm;
}

CategoryModel* CategoryControl::getCategory(QString name,int userId){
    CategoryModel* cm=NULL;
    if(this->connectDb()){
        QString sql="select * from categories where name='"+name+"' and user_id="+QString::number(userId);
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            cm=new CategoryModel();
            cm->setCategoryId(query.value(0).toInt());
            cm->setParentId(query.value(1).toInt());
            cm->setUserId(userId);
            cm->setName(name);
        }
        this->closeDb();
    }
    return cm;
}

QList<CategoryModel*> CategoryControl::getAllCategories(int userId){
    QList<CategoryModel*> cms;
    if(this->connectDb()){
        QString sql = "select * from categories where user_id="+QString::number(userId);
        QSqlQuery query = this->queryDb(sql);
        while(query.next()){
            CategoryModel* cm=new CategoryModel();
            cm->setCategoryId(query.value(0).toInt());
            cm->setParentId(query.value(1).toInt());
            cm->setUserId(userId);
            cm->setName(query.value(3).toString());

            cms.append(cm);
        }
        this->closeDb();
    }
    return cms;
}

bool CategoryControl::addCategory(CategoryModel* categoryModel) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "select max(category_id) from categories";
        QSqlQuery query = this->queryDb(sql);
        int id=0;
        if(query.next()){
            id=query.value(0).toInt();
        }
        id++;
        categoryModel->setName(categoryModel->getName().replace("'","''"));
        categoryModel->setCategoryId(id);
        if(categoryModel->getParentId()==0){
            sql = "insert into categories values("+QString::number(id)+",NULL,"+ QString::number(categoryModel->getUserId())+ ",'" + categoryModel->getName()+"')";
        }else{
            sql = "insert into categories values("+QString::number(id)+"," + QString::number(categoryModel->getParentId())+ ","+ QString::number(categoryModel->getUserId())+ ",'" + categoryModel->getName()+"')";
        }
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

bool CategoryControl::editCategory(CategoryModel* categoryModel) {
    bool result=false;
    if(this->connectDb()){
        categoryModel->setName(categoryModel->getName().replace("'","''"));
        QString sql = "update categories set parent_id=" + QString::number(categoryModel->getParentId()) + ",name='" + categoryModel->getName() +"' where category_id="+QString::number(categoryModel->getCategoryId());
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

bool CategoryControl::deleteCategory(int categoryId,int userId) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "delete from categories where category_id="+QString::number(categoryId)+" and user_id="+QString::number(userId);//codes in this category will be deleted automally
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

