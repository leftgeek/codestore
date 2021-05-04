#include "./headers/searchWidget.h"
#include "./headers/codeTreeWidget.h"
#include "./headers/tabWidget.h"
SearchWidget::SearchWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

SearchWidget::~SearchWidget(){

}

void SearchWidget::setupWidgets(){
    this->setAccessibleName("search");
    this->setAccessibleDescription("web");
    this->searchLineEdit=new QLineEdit();
    this->searchTypeComboBox=new QComboBox();
    this->searchTypeComboBox->addItem("Local");
    this->searchTypeComboBox->addItem("Shared");
    this->searchButton=new QPushButton("Search");
    this->previousButton=new QPushButton("Previous");
    this->nextButton=new QPushButton("Next");
    this->previousButton->setEnabled(false);
    this->nextButton->setEnabled(false);
    this->listWidget=new QListWidget();
    this->listWidget->setAlternatingRowColors(true);
    this->listWidget->setSpacing(5);
    this->pageNow=1;
}

void SearchWidget::setupLayouts(){
    QGridLayout* gridLayout=new QGridLayout();
    gridLayout->addWidget(this->searchTypeComboBox,0,0,1,1);
    gridLayout->addWidget(this->searchLineEdit,0,1,1,1);
    gridLayout->addWidget(this->searchButton,0,2,1,1);

    QHBoxLayout* hLayout=new QHBoxLayout();
    hLayout->addWidget(this->previousButton);
    hLayout->addWidget(this->nextButton);

    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addLayout(gridLayout);
    vLayout->addWidget(this->listWidget);
    vLayout->addLayout(hLayout);

    this->setLayout(vLayout);
}

void SearchWidget::setupActions(){
    QObject::connect(this->searchButton,SIGNAL(clicked()),this,SLOT(onSearch()));
    QObject::connect(this->previousButton,SIGNAL(clicked()),this,SLOT(onPrevious()));
    QObject::connect(this->nextButton,SIGNAL(clicked()),this,SLOT(onNext()));
    QObject::connect(this->listWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onViewFile(QModelIndex)));
}

void SearchWidget::onSearch(){
    QString keywords=this->searchLineEdit->text();
    this->listWidget->clear();
    this->codes.clear();
    if(this->searchTypeComboBox->currentIndex()==0){//local search
        CodeTree* codeTree=CodeTree::getCodeTree();
        this->codes=codeTree->searchAllCodes(keywords);
    }else{//web search
        CodeControl* cc=new CodeControl();
        this->codes=cc->searchAllCodes(keywords,this->pageNow);
        delete(cc);
    }
    for(int i=0;i<codes.size();i++){
        QString name=codes.at(i)->getName();
        QString description=codes.at(i)->getDescription();
        QString item="Name:"+name+"\nDescription:"+description;
        QListWidgetItem* listItem=new QListWidgetItem(item);
        int index=name.lastIndexOf('.');
        QString suffix="txt";
        if(index!=-1){
            suffix=name.mid(name.lastIndexOf('.')+1);
        }
        listItem->setIcon(CodeTreeWidget::getIcon(suffix));
        this->listWidget->addItem(listItem);
    }
}

void SearchWidget::onPrevious(){
    this->pageNow--;
}

void SearchWidget::onNext(){
    this->pageNow++;
}

void SearchWidget::onViewFile(QModelIndex index){
    int i = index.row();
    CodeModel* cm=this->codes.at(i);
    QString name=cm->getName();
    TabWidget* tabWidget=TabWidget::getTabWidget();
    if(this->searchTypeComboBox->currentIndex()==0){//open local file
        tabWidget->openFile("codes/"+name);
    }else{
        TextEditor* textEditor=new TextEditor();
        textEditor->document()->setPlainText(cm->getContent());
        textEditor->setAccessibleName(name);
        textEditor->setAccessibleDescription("web");
        textEditor->setReadOnly(true);
        int index=name.lastIndexOf('.');
        QString suffix="txt";
        if(index!=-1){
            suffix=name.mid(name.lastIndexOf('.')+1);
        }
        textEditor->changeHighlightMode(suffix);

        if(!tabWidget->openTab(textEditor,textEditor->accessibleName())){
            delete(textEditor);
        }
    }

}





