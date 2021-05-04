#include "./headers/replaceWidget.h"
ReplaceWidget* ReplaceWidget::replaceWidget=NULL;
ReplaceWidget::ReplaceWidget(QWidget *parent):QDialog(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

ReplaceWidget::~ReplaceWidget(){

}

void ReplaceWidget::setupWidgets(){
    this->findLabel=new QLabel("Find:");
    this->replaceLabel=new QLabel("Replace with:");
    this->findLineEdit=new QLineEdit();
    this->replaceLineEdit=new QLineEdit();
    this->findBackwardCheckBox=new QCheckBox("Backword");
    this->findCaseSensitiveCheckBox=new QCheckBox("Case sensitive");
    this->findWholeWordsCheckBox=new QCheckBox("Whole words");
    this->findButton=new QPushButton("Find");
    this->replaceButton=new QPushButton("Replace");
}

void ReplaceWidget::setupLayouts(){
    QGridLayout* gridLayout=new QGridLayout();
    gridLayout->addWidget(this->findLabel,0,0,1,1);
    gridLayout->addWidget(this->replaceLabel,1,0,1,1);
    gridLayout->addWidget(this->findLineEdit,0,1,1,1);
    gridLayout->addWidget(this->replaceLineEdit,1,1,1,1);
    gridLayout->addWidget(this->findButton,0,2,1,1);
    gridLayout->addWidget(this->replaceButton,1,2,1,1);
    gridLayout->addWidget(this->findBackwardCheckBox,2,0,1,1);
    gridLayout->addWidget(this->findCaseSensitiveCheckBox,2,1,1,1);
    gridLayout->addWidget(this->findWholeWordsCheckBox,2,2,1,1);

    this->setLayout(gridLayout);
}

void ReplaceWidget::setTextEditor(QPlainTextEdit* textEditor){
    this->textEditor=textEditor;
}

void ReplaceWidget::setupActions(){
    QObject::connect(this->findButton,SIGNAL(clicked()),this,SLOT(onFind()));
    QObject::connect(this->replaceButton,SIGNAL(clicked()),this,SLOT(onReplace()));
}

void ReplaceWidget::onFind(){
    QString findText=this->findLineEdit->text();
    QTextDocument::FindFlags flags;
    if(this->findBackwardCheckBox->isChecked()){
        flags.operator |=(QTextDocument::FindBackward);
    }
    if(this->findCaseSensitiveCheckBox->isChecked()){
        flags.operator |=(QTextDocument::FindCaseSensitively);
    }
    if(this->findWholeWordsCheckBox->isChecked()){
        flags.operator |=(QTextDocument::FindWholeWords);
    }
    this->textEditor->find(findText,flags);
}

void ReplaceWidget::onReplace(){
    QString findText=this->findLineEdit->text();
    QString replaceText=this->replaceLineEdit->text();
}

ReplaceWidget* ReplaceWidget::getReplaceWidget(){
    if(replaceWidget==NULL){
        replaceWidget=new ReplaceWidget();
    }
    return replaceWidget;
}
