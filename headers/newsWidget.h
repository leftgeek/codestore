#ifndef NEWSWIDGET_H
#define NEWSWIDGET_H
#include <QtGui>
class NewsWidget:public QWidget{
    Q_OBJECT
private:
    QLabel* fileLabel;
    QListWidget* fileListWidget;
private slots:

public:
    NewsWidget(QWidget* parent=0);
    ~NewsWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
};
#endif // NEWSWIDGET_H
