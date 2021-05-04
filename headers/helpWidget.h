#ifndef HELPWIDGET_H
#define HELPWIDGET_H
#include <QWidget>
#include <QWebView>
class HelpWidget:public QWidget{
private:
    QWebView* webView;
public:
    HelpWidget(QWidget* parent=0);
    ~HelpWidget();
    void setupWidgets();
};

#endif // HELPWIDGET_H
