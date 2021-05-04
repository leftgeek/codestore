#include <QtGui>
#include "./headers/tabWidget.h"
#include "./headers/newFileWidget.h"
#include "./headers/newCategoryWidget.h"
#include "./headers/codeTreeWidget.h"
TabWidget* TabWidget::tabWidget=NULL;
TabWidget::TabWidget(QWidget* parent):QTabWidget(parent){
    this->setupWidgets();
    this->setupActions();
}

TabWidget::~TabWidget(){

}

TabWidget* TabWidget::getTabWidget(){
    if(tabWidget==NULL){
        tabWidget=new TabWidget();
    }
    return tabWidget;
}

void TabWidget::setupWidgets(){
    this->setTabsClosable(true);
    this->setMovable(true);
    this->setDocumentMode(true);
}

void TabWidget::setupActions(){
    QObject::connect(this,SIGNAL(tabCloseRequested(int)),this,SLOT(onCloseTab(int)));
}

void TabWidget::onCloseTab(int index){
    QWidget* widget=this->widget(index);
    if(widget->accessibleDescription()=="text"){
        TextEditor* textEditor=(TextEditor*)this->widget(index);
        if(textEditor->closeFile()){
            this->removeTab(index);
            delete(textEditor);
        }
    }else{
        this->removeTab(index);
        delete(widget);
    }

}

int TabWidget::findIndex(QString filePath){
    int index=-1;
    for(int i=0;i<this->count();i++){//检查该文件是否已经打开过
        if(this->widget(i)->accessibleDescription()=="text"){
            TextEditor* textEditor=(TextEditor*)this->widget(i);
            if(textEditor->getFilePath()==filePath){
                index=i;
                break;
            }
        }
    }
    return index;
}

void TabWidget::newFile(){
    QString categoryName="categories";
    this->newFile(categoryName);
}

void TabWidget::newFile(QString categoryName){
    NewFileWidget newFileWidget;
    newFileWidget.setCategory(categoryName);
    if(newFileWidget.exec()==QDialog::Accepted){
        CodeModel* codeModel=newFileWidget.getCodeModel();//create new code
        CodeTreeWidget* codeTreeWidget=CodeTreeWidget::getCodeTreeWidget();
        codeTreeWidget->addCode(codeModel);
        QString filePath = "codes/"+codeModel->getName();

        TextEditor* textEditor=new TextEditor();
        if(textEditor->newFile(filePath)){
            textEditor->setAccessibleDescription("text");
            this->addTab(textEditor,filePath.mid(filePath.lastIndexOf("/")+1));
            this->setCurrentIndex(this->count()-1);
            QString fileType="txt";
            int index=filePath.lastIndexOf('.');
            if(index!=-1){
                fileType=filePath.mid(index+1);
            }
            this->setTabIcon(this->currentIndex(),CodeTreeWidget::getIcon(fileType));
        }else{
            delete(textEditor);
        }
    }
}

void TabWidget::openFile(){
    QString fileFilters = tr("C files (*.c)\n"
                           "C++ files (*.cpp)\n"
                           "Java files (*.java)\n"
                           "HTML files (*.html)\n"
                           "All files (*)");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), ".", fileFilters);
    if (!filePath.isEmpty()){
        this->openFile(filePath);
    }
}

void TabWidget::openFile(QString filePath){
    int index=this->findIndex(filePath);
    if(index==-1){
        TextEditor* textEditor=new TextEditor();
        if(textEditor->openFile(filePath)){
            textEditor->setAccessibleDescription("text");
            this->addTab(textEditor,filePath.mid(filePath.lastIndexOf("/")+1));
            this->setCurrentIndex(this->count()-1);
            QString fileType="txt";
            int i=filePath.lastIndexOf('.');
            if(i!=-1){
                fileType=filePath.mid(i+1);
            }
            this->setTabIcon(this->currentIndex(),CodeTreeWidget::getIcon(fileType));
        }else{
            delete(textEditor);
        }
    }else{
        this->setCurrentIndex(index);
    }
}

TextEditor* TabWidget::getCurrentTextEditor(){
    TextEditor* currentTextEditor=NULL;
    if(this->count()>0){
        if(this->currentWidget()->accessibleDescription()=="text"){
            currentTextEditor=(TextEditor*)this->currentWidget();
        }
    }
    return currentTextEditor;
}

void TabWidget::saveFile(QString filePath){
    TextEditor* currentTextEditor=this->getCurrentTextEditor();
    if(currentTextEditor!=NULL){
        currentTextEditor->saveFile(filePath);
    }
}
void TabWidget::closeFile(){
    TextEditor* currentTextEditor=this->getCurrentTextEditor();
    if(currentTextEditor!=NULL){
        if(currentTextEditor->closeFile()){
            this->removeTab(this->currentIndex());
            delete(currentTextEditor);
        }
    }else{
        QWidget* widget=this->widget(this->currentIndex());
        this->removeTab(this->currentIndex());
        delete(widget);
    }
}

bool TabWidget::closeAllFile(){
    bool result;
    int tabCount;
    while(this->count()>0){
        tabCount=this->count();
        this->closeFile();
        if(tabCount==this->count()){
            break;
        }
    }
    if(0==this->count()){
        result=true;
    }else{
        result=false;
    }
    return result;
}

void TabWidget::setTabModified(bool modified){
    if(modified){
        QString title=this->tabText(this->currentIndex());
        if(title.at(title.length()-1)!='*'){
            this->setTabText(this->currentIndex(),title+"*");
        }
    }else{
        QString title=this->tabText(this->currentIndex());
        if(title.at(title.length()-1)=='*'){
            this->setTabText(this->currentIndex(),title.left(title.length()-1));
        }
    }
}

bool TabWidget::openTab(QWidget* widget,QString title){
    bool result=true;
    for(int i=0;i<this->count();i++){
        if(widget->accessibleName()==this->widget(i)->accessibleName()){
            this->setCurrentIndex(i);
            result=false;
            break;
        }
    }
    if(result){
        this->addTab(widget,title);
        this->setCurrentIndex(this->count()-1);
    }
    return result;
}

void TabWidget::updateFilePath(QString oldFilePath,QString newFilePath){
    int index=this->findIndex(oldFilePath);
    if(index!=-1){
        TextEditor* textEditor=(TextEditor*)this->widget(index);
        textEditor->setFilePath(newFilePath);
        this->setTabText(index,newFilePath.mid(newFilePath.lastIndexOf("/")+1));
        QString fileType="txt";
        int i=newFilePath.lastIndexOf('.');
        if(i!=-1){
            fileType=newFilePath.mid(i+1);
        }
        this->setTabIcon(index,CodeTreeWidget::getIcon(fileType));
    }
}







