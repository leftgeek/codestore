#include "./headers/codeTreeWidget.h"
#include "./headers/tabWidget.h"
CodeTreeWidget* CodeTreeWidget::codeTreeWidget=NULL;
CodeTreeWidget::CodeTreeWidget(QWidget* parent):QTreeWidget(parent){
    this->initTree();
    this->setHeaderHidden(true);
}
CodeTreeWidget::~CodeTreeWidget(){

}

CodeTreeWidget* CodeTreeWidget::getCodeTreeWidget(){
    if(codeTreeWidget==NULL){
        codeTreeWidget=new CodeTreeWidget();
    }
    return codeTreeWidget;
}

void CodeTreeWidget::initTree(){
    this->codeTree=CodeTree::getCodeTree();
    QTreeWidget* treeWidget=this->codeTree->getCodeTreeWidget();
    QTreeWidgetItem* rootItem=treeWidget->topLevelItem(0);
    QTreeWidgetItem* rootTreeItem=new QTreeWidgetItem(rootItem->type());
    rootTreeItem->setText(0,rootItem->text(0));
    rootTreeItem->setIcon(0, QIcon(":icon/text/folder"));
    this->addTopLevelItem(rootTreeItem);
    for(int i=0;i<rootItem->childCount();i++){
        this->addTreeItem(rootTreeItem,rootItem->child(i));
    }
    delete(treeWidget);
}

QTreeWidgetItem* CodeTreeWidget::searchItem(QString name){
    QTreeWidgetItem* item=NULL;
    QList<QTreeWidgetItem *> items=this->findItems(name,Qt::MatchRecursive,0);
    if(items.size()>0){
        item=items.at(0);
    }
    return item;
}

QIcon CodeTreeWidget::getIcon(QString suffix){
    QString iconPath=":icon/text/text_plain";
    if(suffix=="c"){
        iconPath=":icon/text/text_c";
    }else if(suffix=="cpp"){
       iconPath=":icon/text/text_cpp";
    }else if(suffix=="java"){
        iconPath=":icon/text/text_java";
    }else if(suffix=="htm"||suffix=="html"){
        iconPath=":icon/text/text_html";
    }
    QIcon codeIcon(iconPath);
    return codeIcon;
}

void CodeTreeWidget::addTreeItem(QTreeWidgetItem* parentItem,QTreeWidgetItem* childItem){
    int type=childItem->type();
    QString name=childItem->text(0);
    QTreeWidgetItem* newItem=new QTreeWidgetItem(type);
    newItem->setText(0,name);
    if(type==0){
        newItem->setIcon(0, QIcon(":icon/text/folder"));
    }else{
        int index=name.lastIndexOf('.');
        QString suffix="txt";
        if(index!=-1){
            suffix=name.mid(name.lastIndexOf('.')+1);
        }
        newItem->setIcon(0, CodeTreeWidget::getIcon(suffix));
    }
    parentItem->addChild(newItem);
    for(int i=0;i<childItem->childCount();i++){
        QTreeWidgetItem* item=childItem->child(i);
        this->addTreeItem(newItem,item);
    }
}

void CodeTreeWidget::addCategory(CategoryModel *categoryModel){
    QString parent=categoryModel->getParentName();
    QTreeWidgetItem * item=this->searchItem(parent);
    if(item!=NULL){
        QTreeWidgetItem* newItem=new QTreeWidgetItem(0);
        newItem->setText(0,categoryModel->getName());
        newItem->setIcon(0, QIcon(":icon/text/folder"));
        item->addChild(newItem);
        CodeTree* codeTree=CodeTree::getCodeTree();
        codeTree->addCategory(categoryModel,parent);
    }
}

void CodeTreeWidget::addCode(CodeModel* codeModel){
    QString parent=codeModel->getCategoryName();
    QTreeWidgetItem * item=this->searchItem(parent);
    if(item!=NULL){
        QString name=codeModel->getName();
        QTreeWidgetItem* newItem=new QTreeWidgetItem(1);
        newItem->setText(0,name);
        int index=name.lastIndexOf('.');
        QString suffix="txt";
        if(index!=-1){
            suffix=name.mid(name.lastIndexOf('.')+1);
        }
        newItem->setIcon(0, CodeTreeWidget::getIcon(suffix));
        item->addChild(newItem);
        this->codeTree->addCode(codeModel,parent);
    }
}
//
bool CodeTreeWidget::modifyCategory(CategoryModel* categoryModel,QString oldName){
    bool result=false;
    if(this->codeTree->modifyCategory(categoryModel,oldName)){
        QTreeWidgetItem * item=this->searchItem(oldName);
        if(item!=NULL){
            item->setText(0,categoryModel->getName());
            result=true;
        }
    }
    return result;
}
//modify parent category
bool CodeTreeWidget::modifyCategory(QString categoryName,QString parentName){
    bool result=false;
    if(this->codeTree->modifyCategory(categoryName,parentName)){
        QTreeWidgetItem * newParent=this->searchItem(parentName);
        if(newParent!=NULL){
            QTreeWidgetItem * item=this->searchItem(categoryName);
            if(item!=NULL){
                item->parent()->removeChild(item);
                newParent->addChild(item);
                newParent->setExpanded(true);
                result=true;
            }
        }
    }
    return result;
}
//modify code id,name,description,share_status
bool CodeTreeWidget::modifyCode(CodeModel* codeModel,QString oldName){
    bool result=false;
    if(oldName!=codeModel->getName()){//update file path
        TabWidget* tabWidget=TabWidget::getTabWidget();
        tabWidget->updateFilePath("codes/"+oldName,"codes/"+codeModel->getName());
    }
    if(this->codeTree->modifyCode(codeModel,oldName)){
        QTreeWidgetItem * item=this->searchItem(oldName);
        if(item!=NULL){
            item->setText(0,codeModel->getName());
            QString name=item->text(0);
            int index=name.lastIndexOf('.');
            QString suffix="txt";
            if(index!=-1){
                suffix=name.mid(name.lastIndexOf('.')+1);
            }
            item->setIcon(0, CodeTreeWidget::getIcon(suffix));
            result=true;
        }
    }
    return result;
}
//modify parent category
bool CodeTreeWidget::modifyCode(QString codeName,QString parentName){
    bool result=false;
    if(this->codeTree->modifyCode(codeName,parentName)){
        QTreeWidgetItem * newParent=this->searchItem(parentName);
        if(newParent!=NULL){
            QTreeWidgetItem * item=this->searchItem(codeName);
            if(item!=NULL){
                item->parent()->removeChild(item);//item will be removed from his old parent
                newParent->addChild(item);//item will be added to his new parent
                newParent->setExpanded(true);//expand new parent
                result=true;
            }
        }
    }
    return result;
}

void CodeTreeWidget::deleteItem(QTreeWidgetItem *item){
    QString name=item->text(0);
    if(name!="categories"){
        if(item->type()==0){//category
            this->codeTree->deleteCategory(name);
        }else{
            this->codeTree->deleteCode(name);
        }
        delete(item);
    }
}

//从服务器端下载分类
void CodeTreeWidget::downloadCategory(int userId){
    CategoryControl cc;
    QList<CategoryModel*> cms=cc.getAllCategories(userId);
    for(int i=0;i<cms.size();i++){
        CategoryModel* serverCategory=cms.at(i);
        CategoryModel* categoryModel=this->codeTree->getCategory(serverCategory->getName());
        if(categoryModel==NULL){
            CategoryModel* parentCategory=cc.getCategory(serverCategory->getParentId());
            serverCategory->setParentName(parentCategory->getName());
            this->addCategory(serverCategory);
            delete(parentCategory);
        }
    }
    cms.clear();
}

//从服务器端下载代码
void CodeTreeWidget::downloadCode(int userId){
    CodeControl cc;
    QList<CodeModel*> cms=cc.getAllCodes(userId);
    CategoryControl cac;
    for(int i=0;i<cms.size();i++){
        CodeModel* serverCode=cms.at(i);
        CodeModel* codeModel=this->codeTree->getCode(serverCode->getName());
        if(codeModel==NULL){//说明本地没有该文件
            CategoryModel* categoryModel=cac.getCategory(serverCode->getCategoryId());
            serverCode->setCategoryName(categoryModel->getName());
            this->addCode(serverCode);
            delete(categoryModel);
        }
    }
    cms.clear();
}

