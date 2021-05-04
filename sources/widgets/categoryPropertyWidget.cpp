#include "./headers/categoryPropertyWidget.h"
#include "./headers/codeTreeWidget.h"
CategoryPropertyWidget::CategoryPropertyWidget(QWidget *parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

CategoryPropertyWidget::~CategoryPropertyWidget(){

}

void CategoryPropertyWidget::setupWidgets(){
    this->nameLabel=new QLabel("Name:");
    this->parentLabel=new QLabel("Parent:");
    this->nameLineEdit=new QLineEdit();
    this->confirmButton=new QPushButton("Confirm");
    this->cancelButton=new QPushButton("Cancel");

    CodeTree* codeTree=CodeTree::getCodeTree();
    this->categoryTree=codeTree->getCategoryComboBox();
}

void CategoryPropertyWidget::setupLayouts(){
    QFormLayout* formLayout=new QFormLayout();
    formLayout->addRow(this->nameLabel,this->nameLineEdit);
    formLayout->addRow(this->parentLabel,this->categoryTree);

    QHBoxLayout* hLayout=new QHBoxLayout();
    hLayout->addWidget(this->confirmButton);
    hLayout->addWidget(this->cancelButton);
    formLayout->addRow(hLayout);
    this->setLayout(formLayout);
}

void CategoryPropertyWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void CategoryPropertyWidget::setParentCategory(QString parent){
    for(int i=0;i<this->categoryTree->count();i++){
        QString categoryName= this->categoryTree->itemData(i).toString();
        if(categoryName==parent){
            this->categoryTree->setCurrentIndex(i);
            break;
        }
    }
}

void CategoryPropertyWidget::showProperty(CategoryModel *categoryModel){
    this->categoryModel=categoryModel;
    this->nameLineEdit->setText(categoryModel->getName());
    this->setParentCategory(categoryModel->getParentName());
}

void CategoryPropertyWidget::onConfirm(){
    CodeTreeWidget* codeTreeWidget=CodeTreeWidget::getCodeTreeWidget();
    QString name=this->nameLineEdit->text();
    QString parentName=this->categoryTree->itemData(this->categoryTree->currentIndex()).toString();
    //name is changed
    if(this->categoryModel->getName()!=name){
        QString oldName=this->categoryModel->getName();
        this->categoryModel->setName(name);
        codeTreeWidget->modifyCategory(this->categoryModel,oldName);
    }
    //parent is changed
    if(this->categoryModel->getParentName()!=parentName){
        this->categoryModel->setParentName(parentName);
        codeTreeWidget->modifyCategory(name,parentName);
    }
}


void CategoryPropertyWidget::onCancel(){

}


