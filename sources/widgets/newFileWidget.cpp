#include "./headers/newFileWidget.h"
#include "./headers/codeTree.h"
NewFileWidget::NewFileWidget(QWidget *parent):CodePropertyWidget(parent){
    this->setWindowTitle("New File");
}

NewFileWidget::~NewFileWidget(){

}

void NewFileWidget::onConfirm(){
    QString name=this->nameLineEdit->text();
    QString categoryName=this->categoryTree->itemData(this->categoryTree->currentIndex()).toString();
    QString description=this->descriptionTextEdit->toPlainText();
    this->codeModel=new CodeModel();
    this->codeModel->setCodeId(0);
    this->codeModel->setName(name);
    this->codeModel->setCategoryName(categoryName);
    this->codeModel->setDescription(description);
    this->codeModel->setShareStatus(this->shareStatusCheckBox->isChecked()?1:0);
    this->accept();
}

void NewFileWidget::onCancel(){
    this->close();
}

CodeModel* NewFileWidget::getCodeModel(){
    return this->codeModel;
}
