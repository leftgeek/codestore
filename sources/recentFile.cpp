#include "./headers/recentFile.h"
#include <QFile>
#include <QTextStream>
RecentFile* RecentFile::recentFile=NULL;
RecentFile::RecentFile(){
    this->initRecentFile();
}

RecentFile::~RecentFile(){

}

RecentFile* RecentFile::getRecentFile(){
    if(recentFile==NULL){
        recentFile=new RecentFile();
    }
    return recentFile;
}

QDomDocument* RecentFile::getDomDocument(){
    return this->domDocument;
}

void RecentFile::initRecentFile(){
    this->filePath="config/recent.xml";
    this->domDocument=new QDomDocument();
    this->openFile(this->filePath);
}

bool RecentFile::openFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)){
        result=this->domDocument->setContent(&file);
        file.close();
    }
    return result;
}

bool RecentFile::saveFile(QString filePath){
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

bool RecentFile::saveFile(){
    return this->saveFile(this->filePath);
}

bool RecentFile::addFile(QString filePath){
    bool result=true;
    QDomElement rootElement=this->domDocument->firstChildElement("files");
    QDomNodeList nodeList=rootElement.childNodes();
    for(int i=1;i<nodeList.size();i++){
        QDomNode node=nodeList.at(i);
        if(node.namedItem("path").toElement().text()==filePath){
            result=false;
            break;
        }
    }
    if(result){
        QDomElement fileElement=this->domDocument->createElement("file");
        QDomElement path=this->domDocument->createElement("path");
        QDomText pathName=this->domDocument->createTextNode(filePath);
        path.appendChild(pathName);
        fileElement.appendChild(path);
        rootElement.appendChild(fileElement);
        this->saveFile();
    }
    return result;
}

bool RecentFile::removeFile(QString filePath){
    bool result=false;
    QDomElement rootElement=this->domDocument->firstChildElement("files");
    QDomNodeList nodeList=rootElement.childNodes();
    for(int i=1;i<nodeList.size();i++){
        QDomNode node=nodeList.at(i);
        if(node.namedItem("path").toElement().text()==filePath){
            rootElement.removeChild(node);
            result=true;
            this->saveFile();
            break;
        }
    }
    return result;
}

QList<QString> RecentFile::getAllFiles(){
    QList<QString> fileList;
    QDomElement rootElement=this->domDocument->firstChildElement("files");
    QDomNodeList nodeList=rootElement.childNodes();
    for(int i=1;i<nodeList.size();i++){
        QString file=nodeList.at(i).namedItem("path").toElement().text();
        fileList.append(file);
    }
    return fileList;
}


