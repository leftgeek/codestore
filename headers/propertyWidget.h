#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H
#include <QtGui>
//属性类，用来显示文件的属性
class PropertyWidget:public QWidget{
    Q_OBJECT
private:
    QWidget* propertyWidget;
public:
    PropertyWidget(QWidget* parent=0);
    ~PropertyWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void setPropertyWidget(QWidget* propertyWidget);
};

#endif // PROPERTYWIDGET_H
