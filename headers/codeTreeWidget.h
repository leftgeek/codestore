#ifndef CODETREEWIDGET_H
#define CODETREEWIDGET_H
#include <QTreeWidget>
#include "./headers/codeTree.h"
class CodeTreeWidget:public QTreeWidget{
private:
    CodeTreeWidget(QWidget* parent=0);
    static CodeTreeWidget* codeTreeWidget;
    CodeTree* codeTree;
public:
    static CodeTreeWidget* getCodeTreeWidget();
    ~CodeTreeWidget();
    void initTree();
    QTreeWidgetItem* searchItem(QString name);
    void addTreeItem(QTreeWidgetItem* parentItem,QTreeWidgetItem* childItem);
    void addCategory(CategoryModel* categoryModel);
    void addCode(CodeModel* codeModel);
    bool modifyCategory(CategoryModel* categoryModel,QString oldName);//
    bool modifyCode(CodeModel* codeModel,QString oldName);//
    bool modifyCategory(QString categoryName,QString parentName);//
    bool modifyCode(QString codeName,QString parentName);//
    static QIcon getIcon(QString suffix);
    void deleteItem(QTreeWidgetItem *item);
    void downloadCategory(int userId);
    void downloadCode(int userId);
};
#endif // CODETREEWIDGET_H
