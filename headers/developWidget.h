#ifndef DEVELOPWIDGET_H
#define DEVELOPWIDGET_H
#include <QtGui>
#include <QDomDocument>
class DevelopWidget:public QWidget{
    Q_OBJECT
private:
    QLabel* fileLabel;
    QListWidget* fileListWidget;
    QPushButton* fileNewButton;
    QPushButton* fileOpenButton;
private slots:
    void onOpenRecentFile(QListWidgetItem* listItem);
public:
    DevelopWidget(QWidget* parent=0);
    ~DevelopWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void initRecentFiles();
};

#endif // DEVELOPWIDGET_H
