#include "./headers/propertyWidget.h"
PropertyWidget::PropertyWidget(QWidget *parent):QWidget(parent){
    this->propertyWidget=NULL;
}

PropertyWidget::~PropertyWidget(){

}

void PropertyWidget::setPropertyWidget(QWidget *propertyWidget){
    if(this->propertyWidget==NULL){
        this->propertyWidget=propertyWidget;
        QVBoxLayout* vLayout=new QVBoxLayout();
        vLayout->addWidget(this->propertyWidget);
        this->setLayout(vLayout);
    }else{
        this->layout()->removeWidget(this->propertyWidget);
        if(this->propertyWidget!=NULL){
            delete(this->propertyWidget);
        }
        this->propertyWidget=propertyWidget;
        this->layout()->addWidget(this->propertyWidget);
    }
}

