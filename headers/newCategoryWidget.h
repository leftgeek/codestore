#ifndef NEWCATEGORYWIDGET_H
#define NEWCATEGORYWIDGET_H
#include "./headers/categoryPropertyWidget.h"
class NewCategoryWidget:public CategoryPropertyWidget{
private slots:
    void onConfirm();
    void onCancel();
public:
    NewCategoryWidget(QWidget* parent=0);
    ~NewCategoryWidget();
    CategoryModel* getCategoryModel();
};

#endif // NEWCATEGORYWIDGET_H
