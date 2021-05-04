#include "./headers/codePropertyWidget.h"
#include "./headers/codeTreeWidget.h"
CodePropertyWidget::CodePropertyWidget(QWidget *parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

CodePropertyWidget::~CodePropertyWidget(){

}

void CodePropertyWidget::setupWidgets(){
    this->nameLabel=new QLabel("Name:");
    this->categoryLabel=new QLabel("Category:");
    this->descriptionLabel=new QLabel("Description:");
    this->shareStatusLabel=new QLabel("Share:");
    this->nameLineEdit=new QLineEdit();
    this->descriptionTextEdit=new QTextEdit();
    this->shareStatusCheckBox=new QCheckBox();
    this->confirmButton=new QPushButton("Confirm");
    this->cancelButton=new QPushButton("Cancel");

    CodeTree* codeTree=CodeTree::getCodeTree();
    this->categoryTree=codeTree->getCategoryComboBox();
}

void CodePropertyWidget::setupLayouts(){
    QFormLayout* formLayout=new QFormLayout();
    formLayout->addRow(this->nameLabel,this->nameLineEdit);
    formLayout->addRow(this->categoryLabel,this->categoryTree);
    formLayout->addRow(this->descriptionLabel,this->descriptionTextEdit);
    formLayout->addRow(this->shareStatusLabel,this->shareStatusCheckBox);
    QHBoxLayout* hLayout=new QHBoxLayout();
    hLayout->addWidget(this->confirmButton);
    hLayout->addWidget(this->cancelButton);
    formLayout->addRow(hLayout);
    this->setLayout(formLayout);
}

void CodePropertyWidget::setupActions(){
    QObject::connect(this->confirmButton,SIGNAL(clicked()),this,SLOT(onConfirm()));
    QObject::connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(onCancel()));
}

void CodePropertyWidget::setCategory(QString category){
    for(int i=0;i<this->categoryTree->count();i++){
        QString categoryName= this->categoryTree->itemData(i).toString();
        if(categoryName==category){
            this->categoryTree->setCurrentIndex(i);
            break;
        }
    }
}

void CodePropertyWidget::showProperty(CodeModel *codeModel){
    this->codeModel=codeModel;
    this->nameLineEdit->setText(codeModel->getName());
    this->descriptionTextEdit->setPlainText(codeModel->getDescription());
    this->shareStatusCheckBox->setChecked(codeModel->getShareStatus()==1);
    this->setCategory(codeModel->getCategoryName());
}

void CodePropertyWidget::onConfirm(){
    CodeTreeWidget* codeTreeWidget=CodeTreeWidget::getCodeTreeWidget();
    QString name=this->nameLineEdit->text();
    QString description=this->descriptionTextEdit->toPlainText();
    QString categoryName=this->categoryTree->itemData(this->categoryTree->currentIndex()).toString();
    //name,description,share_status is changed
    if(this->codeModel->getName()!=name||this->codeModel->getDescription()!=description){
        QString oldName=this->codeModel->getName();
        this->codeModel->setName(name);
        this->codeModel->setDescription(description);
        this->codeModel->setShareStatus(this->shareStatusCheckBox->isChecked()?1:0);
        codeTreeWidget->modifyCode(this->codeModel,oldName);
    }
    //parent is changed

    if(this->codeModel->getCategoryName()!=categoryName){
        this->codeModel->setCategoryName(categoryName);
        codeTreeWidget->modifyCode(name,categoryName);
    }

}


void CodePropertyWidget::onCancel(){

}
