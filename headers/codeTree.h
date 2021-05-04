#ifndef CODETREE_H
#define CODETREE_H
//代码tree类
#include <QDomDocument>
#include "./headers/category.h"
#include "./headers/code.h"
//
class CodeTree{
private:
    QString filePath;
    QDomDocument* domDocument;
    static CodeTree* codeTree;
    CodeTree();
public:
    void initCodeTree();
    bool openFile(QString filePath);
    bool saveFile(QString filePath);
    bool saveFile();
    ~CodeTree();
    static CodeTree* getCodeTree();
    QDomDocument* getDomDocument();
    CategoryModel* getCategory(QString name);
    CategoryModel* getCategory(QDomElement element);
    CodeModel* getCode(QString name);
    CodeModel* getCode(QDomElement element);
    QDomElement getCategoryElement(QString name);
    QDomElement getCodeElement(QString name);
    bool addCategory(CategoryModel* categoryModel,QString parentName);//add a category
    bool addCode(CodeModel* codeModel,QString parentName);//
    bool modifyCategory(CategoryModel* categoryModel,QString name);//
    bool modifyCode(CodeModel* codeModel,QString name);//
    bool modifyCategory(QString categoryName,QString parentName);//
    bool modifyCode(QString codeName,QString parentName);//
    bool deleteCategory(QString name);//
    void deleteAllCodes(QDomElement categoryElement);//
    bool deleteCode(QString name);//
    QTreeWidget* getCodeTreeWidget();
    QComboBox* getCategoryComboBox();
    void addCategoryComboItem(QComboBox* comboBox, QDomElement element,QString space);
    void addCodeTreeItem(QTreeWidgetItem *treeItem, QDomElement element);
    void syncCode(int userId);
    void syncItem(QDomElement element,int userId);
    QList<CodeModel *> searchAllCodes(QString keywords);
};

#endif // CODETREE_H
