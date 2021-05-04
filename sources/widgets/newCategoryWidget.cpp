#include "./headers/newCategoryWidget.h"
NewCategoryWidget::NewCategoryWidget(QWidget *parent):CategoryPropertyWidget(parent){
    this->setWindowTitle("New Category");
}

NewCategoryWidget::~NewCategoryWidget(){

}

void NewCategoryWidget::onConfirm(){
    QString name=this->nameLineEdit->text();
    QString parentName=this->categoryTree->itemData(this->categoryTree->currentIndex()).toString();
    this->categoryModel=new CategoryModel();
    this->categoryModel->setCategoryId(0);
    this->categoryModel->setName(name);
    this->categoryModel->setParentName(parentName);
    this->accept();
}

void NewCategoryWidget::onCancel(){
    this->close();
}

CategoryModel* NewCategoryWidget::getCategoryModel(){
    return this->categoryModel;
}
