#ifndef STARTPAGEWIDGET_H
#define STARTPAGEWIDGET_H
#include <QtGui>
#include "./headers/developWidget.h"
#include "./headers/personalCenterWidget.h"
#include "./headers/newsWidget.h"
class StartPageWidget:public QWidget{
    Q_OBJECT
private:
    QListWidget* listWidget;
    QStackedWidget* stackedWidget;
    DevelopWidget* developWidget;
    PersonalCenterWidget* personalCenterWidget;
    NewsWidget* newsWidget;
private slots:
    void changePage(QListWidgetItem *current, QListWidgetItem *previous);
public:
    StartPageWidget(QWidget* parent=0);
    ~StartPageWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
};

#endif // STARTPAGEWIDGET_H
