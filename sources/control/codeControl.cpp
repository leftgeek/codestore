#include "./headers/code.h"
#include "./headers/category.h"
CodeControl::CodeControl():Database(){

}

CodeControl::~CodeControl(){

}

CodeModel* CodeControl::getCode(int codeId){
    CodeModel* cm=NULL;
    if(this->connectDb()){
        QString sql="select * from codes where code_id="+QString::number(codeId);
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            cm=new CodeModel();
            cm->setCodeId(codeId);
            cm->setCategoryId(query.value(1).toInt());
            cm->setName(query.value(2).toString());
            cm->setDescription(query.value(3).toString());
            cm->setContent(query.value(4).toString());
            cm->setShareStatus(query.value(5).toInt());
        }
        this->closeDb();
    }
    return cm;
}
CodeModel* CodeControl::getCode(QString name, int userId){
    CodeModel* cm=NULL;
    if(this->connectDb()){
        QString sql="select * from codes where name='"+name+"' and category_id in(select category_id from categories where user_id="+QString::number(userId)+")";
        QSqlQuery query = this->queryDb(sql);
        if(query.next()){
            cm=new CodeModel();
            cm->setCodeId(query.value(0).toInt());
            cm->setCategoryId(query.value(1).toInt());
            cm->setName(name);
            cm->setDescription(query.value(3).toString());
            cm->setContent(query.value(4).toString());
            cm->setShareStatus(query.value(5).toInt());
        }
        this->closeDb();
    }
    return cm;
}

QList<CodeModel*> CodeControl::getAllCodes(int userId){
    QList<CodeModel*> cms;
    if(this->connectDb()){
        QString sql = "select * from codes where category_id in(select category_id from categories where user_id="+QString::number(userId)+")";
        QSqlQuery query = this->queryDb(sql);
        while(query.next()){
            CodeModel* cm=new CodeModel();
            cm->setCodeId(query.value(0).toInt());
            cm->setCategoryId(query.value(1).toInt());
            cm->setName(query.value(2).toString());
            cm->setDescription(query.value(3).toString());
            cm->setContent(query.value(4).toString());
            cm->setShareStatus(query.value(5).toInt());
            cms.append(cm);
        }
        this->closeDb();
    }
    return cms;
}

QList<CodeModel*> CodeControl::searchAllCodes(QString keywords,int pageNow){
    int pageSize=10;
    QList<CodeModel*> cms;
    if(this->connectDb()){
        keywords=keywords.trimmed();
        keywords=keywords.replace(QRegExp(" +"),"%");
        QString sql = "select * from codes where share_status=1 and description like '%"+keywords+"%'";
        if(pageNow>0){
            sql += " limit " + QString::number((pageNow - 1)*pageSize) + "," + QString::number(pageSize);
        }
        QSqlQuery query = this->queryDb(sql);
        while(query.next()){
            CodeModel* cm=new CodeModel();
            cm->setCodeId(query.value(0).toInt());
            cm->setCategoryId(query.value(1).toInt());
            cm->setName(query.value(2).toString());
            cm->setDescription(query.value(3).toString());
            cm->setContent(query.value(4).toString());
            cm->setShareStatus(query.value(5).toInt());
            cms.append(cm);
        }
        this->closeDb();
    }
    return cms;
}

bool CodeControl::addCode(CodeModel* codeModel) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "select max(code_id) from codes";
        QSqlQuery query = this->queryDb(sql);
        int id=0;
        if(query.next()){
            id=query.value(0).toInt();
        }
        id++;
        codeModel->setCodeId(id);
        codeModel->setName(codeModel->getName().replace("'","''"));
        codeModel->setDescription(codeModel->getDescription().replace("'","''"));
        codeModel->setContent(codeModel->getContent().replace("'","''"));
        sql = "insert into codes values("+QString::number(id)+"," + QString::number(codeModel->getCategoryId())+ ",'" + codeModel->getName()+ "','" + codeModel->getDescription()+ "','" + codeModel->getContent()+ "'," + QString::number(codeModel->getShareStatus())+ ")";
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

bool CodeControl::editCode(CodeModel* codeModel) {
    bool result=false;
    if(this->connectDb()){
        codeModel->setName(codeModel->getName().replace("'","''"));
        codeModel->setDescription(codeModel->getDescription().replace("'","''"));
        codeModel->setContent(codeModel->getContent().replace("'","''"));
        QString sql = "update codes set category_id=" + QString::number(codeModel->getCategoryId()) + ",name='" + codeModel->getName()+ "',description='" + codeModel->getDescription()+ "',content='" + codeModel->getContent()+ "',share_status=" + QString::number(codeModel->getShareStatus())+ " where code_id="+QString::number(codeModel->getCodeId());
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}

bool CodeControl::deleteCode(int codeId, int userId) {
    bool result=false;
    if(this->connectDb()){
        QString sql = "delete from codes where code_id="+QString::number(codeId)+" and category_id in(select category_id from categories where user_id="+QString::number(userId)+")";
        this->queryDb(sql);
        result=true;
        this->closeDb();
    }
    return result;
}


