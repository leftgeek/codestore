#ifndef CATEGORYPROPERTYWIDGET_H
#define CATEGORYPROPERTYWIDGET_H
#include <QtGui>
#include "./headers/category.h"
class CategoryPropertyWidget:public QDialog{
    Q_OBJECT
protected:
    QLabel* nameLabel;
    QLabel* parentLabel;
    QLineEdit* nameLineEdit;
    QComboBox* categoryTree;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    CategoryModel* categoryModel;
protected slots:
    virtual void onConfirm();
    virtual void onCancel();
public:
    CategoryPropertyWidget(QWidget* parent=0);
    ~CategoryPropertyWidget();
    virtual void setupWidgets();
    virtual void setupLayouts();
    virtual void setupActions();
    virtual void setParentCategory(QString parent);
    void showProperty(CategoryModel* categoryModel);
};
#endif // CATEGORYPROPERTYWIDGET_H
