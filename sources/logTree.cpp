#include "./headers/user.h"
#include "./headers/logTree.h"
#include "./headers/category.h"
#include "./headers/codeTree.h"
#include <QFile>
LogTree* LogTree::logTree=NULL;
LogTree::LogTree(){
    this->initLogTree();
}

LogTree::~LogTree(){

}

LogTree* LogTree::getLogTree(){
    if(logTree==NULL){
        logTree=new LogTree();
    }
    return logTree;
}

QDomDocument* LogTree::getDomDocument(){
    return this->domDocument;
}

void LogTree::initLogTree(){
    this->filePath="config/log.xml";
    this->domDocument=new QDomDocument();
    this->openFile(this->filePath);
}

bool LogTree::openFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        result=this->domDocument->setContent(&file);
        file.close();
    }
    return result;
}

bool LogTree::saveFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        this->domDocument->save(out,4);
        file.close();
        result=true;
    }
    return result;
}

bool LogTree::saveFile(){
    return this->saveFile(this->filePath);
}

bool LogTree::addLog(QString type,int id){
    bool result=true;
    QDomElement operation=this->domDocument->createElement("operation");
    operation.setAttribute("type",type);
    QDomElement operationId=this->domDocument->createElement("id");
    QDomText idText=this->domDocument->createTextNode(QString::number(id));
    operationId.appendChild(idText);
    operation.appendChild(operationId);
    this->domDocument->firstChildElement("operations").appendChild(operation);
    return result;
}

//先读取日志文件，对服务器端进行删除操作，再遍历codeTree，对服务器端进行修改和添加操作，最后再遍历服务器端的所有分类和代码，对本地文件进行添加操作，
//每次对服务器端进行修改时，用本地文件内容直接覆盖服务器端文件（代码）
bool LogTree::syncLog(int userId){
    bool result=false;
    QDomElement rootElement=this->domDocument->firstChildElement("operations");
    QDomNodeList nodeList=rootElement.childNodes();
    for(int i=1;i<nodeList.size();i++){
        QDomElement operation=nodeList.at(i).toElement();
        QString type=operation.attributeNode("type").value();//type
        int id=operation.namedItem("id").toElement().text().toInt();
        if(type=="category"){
            CategoryControl cc;
            if(cc.deleteCategory(id,userId)){

            }
        }else if(type=="code"){
            CodeControl cc;
            if(cc.deleteCode(id,userId)){

            }
        }
        rootElement.removeChild(operation);
    }
    this->saveFile();
    return result;
}

















