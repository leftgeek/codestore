#include "./headers/importFileWidget.h"
#include "./headers/codeTree.h"
ImportFileWidget::ImportFileWidget(QWidget *parent):CodePropertyWidget(parent){
    this->setWindowTitle("Import File");
}

ImportFileWidget::~ImportFileWidget(){

}

void ImportFileWidget::onConfirm(){
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

void ImportFileWidget::onCancel(){
    this->close();
}
