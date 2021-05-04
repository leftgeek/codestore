#include "./headers/codeTree.h"
#include "./headers/user.h"
#include "./headers/logTree.h"
#include <QFile>
CodeTree* CodeTree::codeTree;
CodeTree::CodeTree(){
    this->initCodeTree();
}

CodeTree::~CodeTree(){

}

CodeTree* CodeTree::getCodeTree(){
    if(codeTree==NULL){
        codeTree=new CodeTree();
    }
    return codeTree;
}

QDomDocument* CodeTree::getDomDocument(){
    return this->domDocument;
}

void CodeTree::initCodeTree(){
    this->filePath="config/category.xml";
    this->domDocument=new QDomDocument();
    this->openFile(this->filePath);
}

bool CodeTree::openFile(QString filePath){
    bool result=false;
    QFile* file=new QFile(filePath);
    if (file->open(QIODevice::ReadOnly | QIODevice::Text)){
        result=this->domDocument->setContent(file);
        file->close();
    }
    delete(file);
    return result;
}

bool CodeTree::saveFile(QString filePath){
    bool result=false;
    QFile* file=new QFile(filePath);
    if (file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(file);
        this->domDocument->save(out,4);
        file->close();
        result=true;
    }
    delete(file);
    return result;
}

bool CodeTree::saveFile(){
    return this->saveFile(this->filePath);
}

//通过名字查找分类模型
CategoryModel* CodeTree::getCategory(QString name){
    QDomElement categoryElement=this->getCategoryElement(name);
    CategoryModel* categoryModel=NULL;
    if(!categoryElement.isNull()){
        categoryModel=this->getCategory(categoryElement);
    }
    return categoryModel;
}
//将分类元素转换为数据库分类模型
CategoryModel* CodeTree::getCategory(QDomElement categoryElement){
    CategoryModel* categoryModel=NULL;
    if(!categoryElement.isNull()){
        categoryModel=new CategoryModel();
        QString categoryName=categoryElement.namedItem("name").toElement().text();
        categoryModel->setCategoryId(categoryElement.attribute("category_id").toInt());
        categoryModel->setName(categoryName);
        categoryModel->setParentName(categoryElement.parentNode().parentNode().namedItem("name").toElement().text());
    }
    return categoryModel;
}
//通过名字查找代码模型
CodeModel* CodeTree::getCode(QString name){
    QDomElement codeElement=this->getCodeElement(name);
    CodeModel* codeModel=NULL;
    if(!codeElement.isNull()){
        codeModel=this->getCode(codeElement);
    }
    return codeModel;
}
//将代码元素转换为数据库代码模型
CodeModel* CodeTree::getCode(QDomElement codeElement){
    CodeModel* codeModel=NULL;
    if(!codeElement.isNull()){
        codeModel=new CodeModel();
        QString codeName=codeElement.namedItem("name").toElement().text();
        codeModel->setCodeId(codeElement.attribute("code_id").toInt());
        codeModel->setName(codeName);
        codeModel->setCategoryName(codeElement.parentNode().parentNode().namedItem("name").toElement().text());
        codeModel->setDescription(codeElement.namedItem("description").toElement().text());
        codeModel->setShareStatus(codeElement.namedItem("share_status").toElement().text().toInt());
    }
    return codeModel;
}
//通过名字查找分类元素
QDomElement CodeTree::getCategoryElement(QString name){
    QDomElement categoryElement;
    QDomNodeList categories=this->domDocument->elementsByTagName("category");
    for(int i=0;i<categories.size();i++){
        QDomElement element= categories.at(i).toElement();
        QString categoryName=element.namedItem("name").toElement().text();
        if(name==categoryName){
            categoryElement=element;
            break;
        }
    }
    return categoryElement;
}
//通过名字查找代码元素
QDomElement CodeTree::getCodeElement(QString name){
    QDomElement codeElement;
    QDomNodeList codes=this->domDocument->elementsByTagName("code");
    for(int i=0;i<codes.size();i++){
        QDomElement element= codes.at(i).toElement();
        QString codeName=element.namedItem("name").toElement().text();
        if(name==codeName){
            codeElement=element;
            break;
        }
    }
    return codeElement;
}
//向dom树中添加分类节点
bool CodeTree::addCategory(CategoryModel* categoryModel,QString parentName){
    bool result=true;
    QDomElement parentElement=this->getCategoryElement(parentName);
    //<category category_id="category_id"></category>
    QDomElement newCategory=this->domDocument->createElement("category");
    newCategory.setAttribute("category_id",categoryModel->getCategoryId());
    //<name>categoryname</name>
    QDomElement categoryName=this->domDocument->createElement("name");
    QDomText nameText = this->domDocument->createTextNode(categoryModel->getName());
    categoryName.appendChild(nameText);
    /*
        <categories>
            <name>categories</name>
        </categories>
    */
    QDomElement categories=this->domDocument->createElement("categories");
    QDomElement categoriesName=this->domDocument->createElement("name");
    QDomText categoriesText = this->domDocument->createTextNode("categories");
    categoriesName.appendChild(categoriesText);
    categories.appendChild(categoriesName);
    /*
        <codes>
            <name>codes</name>
        </codes>
    */
    QDomElement codes=this->domDocument->createElement("codes");
    QDomElement codesName=this->domDocument->createElement("name");
    QDomText codesText = this->domDocument->createTextNode("codes");
    codesName.appendChild(codesText);
    codes.appendChild(codesName);
    /*finally:
        <category category_id="category_id">
            <name>categoryname</name>
            <categories>
                <name>categories</name>
            </categories>
            <codes>
                <name>codes</name>
            </codes>
        </category>
    */
    newCategory.appendChild(categoryName);
    newCategory.appendChild(categories);
    newCategory.appendChild(codes);
    parentElement.namedItem("categories").appendChild(newCategory);
    this->saveFile();
    return result;
}
//向dom树中添加代码节点
bool CodeTree::addCode(CodeModel* codeModel,QString parentName){
    bool result=true;
    QDomElement parentElement=this->getCategoryElement(parentName);
    QDomElement newCode=this->domDocument->createElement("code");
    newCode.setAttribute("code_id",codeModel->getCodeId());

    QDomElement codeName=this->domDocument->createElement("name");
    QDomText nameText = this->domDocument->createTextNode(codeModel->getName());
    codeName.appendChild(nameText);
    newCode.appendChild(codeName);

    QDomElement codeDescription=this->domDocument->createElement("description");
    QDomText descriptionText = this->domDocument->createTextNode(codeModel->getDescription());
    codeDescription.appendChild(descriptionText);
    newCode.appendChild(codeDescription);

    QDomElement codeShareStatus=this->domDocument->createElement("share_status");
    QDomText shareStatusText = this->domDocument->createTextNode(QString::number(codeModel->getShareStatus()));
    codeShareStatus.appendChild(shareStatusText);
    newCode.appendChild(codeShareStatus);
    parentElement.namedItem("codes").appendChild(newCode);
    this->saveFile();
    return result;
}
//修改分类名称，id
bool CodeTree::modifyCategory(CategoryModel* categoryModel,QString name){
    bool result=true;
    QDomElement category=this->getCategoryElement(name);
    QDomElement categoryName=this->domDocument->createElement("name");
    QDomText nameText = this->domDocument->createTextNode(categoryModel->getName());
    categoryName.appendChild(nameText);
    category.replaceChild(categoryName,category.namedItem("name"));//update name
    category.setAttribute("category_id",categoryModel->getCategoryId());//update id
    this->saveFile();
    return result;
}
//修改代码名称，id，描述，分享状态
bool CodeTree::modifyCode(CodeModel* codeModel,QString name){
    bool result=true;
    QDomElement code=this->getCodeElement(name);

    code.setAttribute("code_id",codeModel->getCodeId());//update id

    QDomElement codeName=this->domDocument->createElement("name");
    QDomText nameText = this->domDocument->createTextNode(codeModel->getName());
    codeName.appendChild(nameText);
    code.replaceChild(codeName,code.namedItem("name"));//update name

    QDomElement codeDescription=this->domDocument->createElement("description");
    QDomText descriptionText = this->domDocument->createTextNode(codeModel->getDescription());
    codeDescription.appendChild(descriptionText);
    code.replaceChild(codeDescription,code.namedItem("description"));//update description

    QDomElement codeShareStatus=this->domDocument->createElement("share_status");
    QDomText shareStatusText = this->domDocument->createTextNode(QString::number(codeModel->getShareStatus()));
    codeShareStatus.appendChild(shareStatusText);
    code.replaceChild(codeShareStatus,code.namedItem("share_status"));//update share_status

    QFile file("codes/"+name);
    if(file.exists()){
        result = file.rename("codes/"+codeModel->getName());//update file name in disk
    }
    this->saveFile();
    return result;
}
//修改分类的父分类
bool CodeTree::modifyCategory(QString categoryName,QString parentName){
    bool result=true;
    QDomElement category=this->getCategoryElement(categoryName);
    QDomNode oldParent=category.parentNode().parentNode();//old parent
    QDomElement newParent=this->getCategoryElement(parentName);
    if(oldParent==newParent){
        result=false;
    }else{
        oldParent.namedItem("categories").removeChild(category);
        newParent.namedItem("categories").appendChild(category);
    }
    this->saveFile();
    return result;
}
//修改代码的分类
bool CodeTree::modifyCode(QString codeName,QString parentName){
    bool result=true;
    QDomElement code=this->getCodeElement(codeName);
    QDomNode oldParent=code.parentNode().parentNode();//old parent
    QDomElement newParent=this->getCategoryElement(parentName);
    if(oldParent==newParent){
        result=false;
    }else{
        oldParent.namedItem("codes").removeChild(code);
        newParent.namedItem("codes").appendChild(code);
    }
    this->saveFile();
    return result;
}
//删除某个分类及其下的所有代码在磁盘上的文件
bool CodeTree::deleteCategory(QString name){
    bool result=true;
    QDomElement category=this->getCategoryElement(name);
    this->deleteAllCodes(category);
    int categoryId=category.attribute("category_id").toInt();
    if(categoryId!=0){
        LogTree* logTree=LogTree::getLogTree();
        logTree->addLog("category",categoryId);
        logTree->saveFile();
    }
    QDomNode parentNode=category.parentNode();
    parentNode.removeChild(category);
    this->saveFile();
    return result;
}
//删除某个分类下的所有代码在磁盘上的文件
void CodeTree::deleteAllCodes(QDomElement element){
    QDomNodeList categories=element.namedItem("categories").childNodes();
    for(int i=1;i<categories.size();i++){
        QDomElement categoryElement=categories.at(i).toElement();
        this->deleteAllCodes(categoryElement);
    }

    QDomNodeList codes=element.namedItem("codes").childNodes();
    for(int i=1;i<codes.size();i++){
        QDomElement codeElement=categories.at(i).toElement();
        QFile file("codes/"+codeElement.namedItem("name").toElement().text());
        if(file.exists()){
            file.remove();
        }
    }
}
//删除代码和其在磁盘上的文件
bool CodeTree::deleteCode(QString name){
    bool result=true;
    QDomElement code=this->getCodeElement(name);
    int codeId=code.attribute("code_id").toInt();
    if(codeId!=0){
        LogTree* logTree=LogTree::getLogTree();
        logTree->addLog("code",codeId);
        logTree->saveFile();
    }
    QDomNode parentNode=code.parentNode();
    parentNode.removeChild(code);
    this->saveFile();
    QFile file("codes/"+name);
    if(file.exists()){
        result = file.remove();
    }
    return result;
}

//添加分类和代码树项
void CodeTree::addCodeTreeItem(QTreeWidgetItem *treeItem, QDomElement element){
    QDomNodeList categories=element.namedItem("categories").childNodes();
    for(int i=1;i<categories.size();i++){
        QTreeWidgetItem* treeWidgetItem=new QTreeWidgetItem(0);
        treeWidgetItem->setText(0,categories.at(i).namedItem("name").toElement().text());
        this->addCodeTreeItem(treeWidgetItem,categories.at(i).toElement());
        treeItem->addChild(treeWidgetItem);
    }

    QDomNodeList codes=element.namedItem("codes").childNodes();
    for(int i=1;i<codes.size();i++){
        QTreeWidgetItem* treeWidgetItem=new QTreeWidgetItem(1);
        treeWidgetItem->setText(0,codes.at(i).namedItem("name").toElement().text());
        treeItem->addChild(treeWidgetItem);
    }
}

//递归添加分类树项
void CodeTree::addCategoryComboItem(QComboBox* comboBox, QDomElement element,QString space){
    QDomNodeList categories=element.namedItem("categories").childNodes();
    for(int i=1;i<categories.size();i++){
        QDomElement domElement=categories.at(i).toElement();
        QString name=domElement.namedItem("name").toElement().text();
        this->addCategoryComboItem(comboBox,domElement,space+"    ");
        comboBox->addItem(space+name,name);
    }
}
//生成分类树下拉列表
QComboBox* CodeTree::getCategoryComboBox(){
    QComboBox* categoryComboBox=new QComboBox();
    categoryComboBox->addItem("categories","categories");
    QDomElement rootElement=this->domDocument->firstChildElement("category");
    QString space="    ";
    this->addCategoryComboItem(categoryComboBox, rootElement,space);
    return categoryComboBox;
}

//生成代码树
QTreeWidget* CodeTree::getCodeTreeWidget(){
    QTreeWidget* codeTree=new QTreeWidget();
    QTreeWidgetItem* rootTreeItem=new QTreeWidgetItem(0);
    codeTree->addTopLevelItem(rootTreeItem);
    QDomElement rootElement=this->domDocument->firstChildElement("category");
    rootTreeItem->setText(0,rootElement.namedItem("name").toElement().text());
    this->addCodeTreeItem(rootTreeItem,rootElement);
    codeTree->setHeaderHidden(true);
    return codeTree;
}

QList<CodeModel *> CodeTree::searchAllCodes(QString keywords){
    QList<CodeModel *> codeList;
    QDomNodeList codes=this->domDocument->elementsByTagName("code");
    for(int i=0;i<codes.size();i++){
        QDomElement element= codes.at(i).toElement();
        QString description=element.namedItem("description").toElement().text();
        if(description.contains(keywords,Qt::CaseInsensitive)){
            CodeModel* codeModel=this->getCode(element);
            codeList.append(codeModel);
        }
    }
    return codeList;
}

//
void CodeTree::syncItem(QDomElement element,int userId){
    QDomNodeList categories=element.namedItem("categories").childNodes();
    int parentId=element.attribute("category_id").toInt();
    for(int i=1;i<categories.size();i++){
        QDomElement categoryElement=categories.at(i).toElement();
        CategoryControl cc;
        CategoryModel* categoryModel=this->getCategory(categoryElement);
        categoryModel->setParentId(parentId);
        categoryModel->setUserId(userId);
        if(categoryModel->getCategoryId()==0){//add new category to server and update local category's id
            CategoryModel* cm = cc.getCategory(categoryModel->getName(),userId);
            QString title="Input a new name";
            QString labelString="New category name for "+categoryModel->getName();
            while(cm!=NULL){
                //alert to modify category name
                bool ok;
                QString newName = QInputDialog::getText(0, title,labelString, QLineEdit::Normal, categoryModel->getName(), &ok);
                if (ok && !newName.isEmpty()){
                    categoryModel->setName(newName);
                    cm = cc.getCategory(categoryModel->getName(),userId);
                }
            }
            cc.addCategory(categoryModel);
            categoryElement.setAttribute("category_id",categoryModel->getCategoryId());
        }else{//modify category at server
            cc.editCategory(categoryModel);
        }
        if(categoryModel!=NULL){
            delete(categoryModel);
        }
        this->syncItem(categoryElement,userId);
    }

    QDomNodeList codes=element.namedItem("codes").childNodes();
    for(int i=1;i<codes.size();i++){
        QDomElement codeElement=codes.at(i).toElement();
        CodeControl cc;
        CodeModel* codeModel=this->getCode(codeElement);//codeModel is local code
        codeModel->setCategoryId(parentId);

        QFile file("codes/"+codeModel->getName());
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);
            QString content = in.readAll();
            codeModel->setContent(content);
            file.close();
        }
        if(codeModel->getCodeId()==0){//add new code to server and update local code's id
            CodeModel* cm = cc.getCode(codeModel->getName(),userId);//cm is server code
            QString title="Input a new name";
            QString labelString="New code name for "+codeModel->getName();
            while(cm!=NULL){
                //alert to modify code name
                bool ok;
                QString newName = QInputDialog::getText(0, title,labelString, QLineEdit::Normal, codeModel->getName(), &ok);
                if (ok && !newName.isEmpty()){
                    codeModel->setName(newName);
                    cm = cc.getCode(codeModel->getName(),userId);
                }
            }
            cc.addCode(codeModel);
            codeElement.setAttribute("code_id",codeModel->getCodeId());
        }else{//modify category at server
            cc.editCode(codeModel);
        }
        if(codeModel!=NULL){
            delete(codeModel);
        }
    }
}

void CodeTree::syncCode(int userId){
    QDomElement rootElement=this->domDocument->firstChildElement("category");
    int categoryId=rootElement.attribute("category_id").toInt();
    if(categoryId==0){
        CategoryControl cc;
        CategoryModel* categoryModel = cc.getCategory("categories",userId);//rootElement.namedItem("name").toElement().text()="categories"
        rootElement.setAttribute("category_id",categoryModel->getCategoryId());
        delete(categoryModel);
    }
    this->syncItem(rootElement,userId);
    this->saveFile();
}






