#ifndef TABWIDGET_H
#define TABWIDGET_H
#include <QTabWidget>
#include "./headers/textEditor.h"
class TabWidget:public QTabWidget{
    Q_OBJECT
private:
    static TabWidget* tabWidget;
    TabWidget(QWidget* parent=0);
protected slots:
    void onCloseTab(int index);
public slots:
    void newFile();
    void openFile();
public:
    static TabWidget* getTabWidget();
    ~TabWidget();
    void setupWidgets();
    void setupActions();
    int findIndex(QString filePath);
    void newFile(QString categoryName);
    void openFile(QString filePath);
    TextEditor* getCurrentTextEditor();
    void saveFile(QString filePath);
    void closeFile();
    bool closeAllFile();
    void setTabModified(bool modified);
    bool openTab(QWidget* widget,QString title);
    void updateFilePath(QString oldFilePath,QString newFilePath);
};
#endif // TABWIDGET_H
