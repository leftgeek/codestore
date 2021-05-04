#include "./headers/developWidget.h"
#include "./headers/tabWidget.h"
#include "./headers/codeTreeWidget.h"
#include "./headers/recentFile.h"
DevelopWidget::DevelopWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
    this->initRecentFiles();
}

DevelopWidget::~DevelopWidget(){

}

void DevelopWidget::setupWidgets(){
    this->fileLabel=new QLabel("Recent Files");
    this->fileLabel->setFont(QFont("Ubuntu",18,QFont::Bold));
    this->fileListWidget=new QListWidget();
    this->fileListWidget->setAlternatingRowColors(true);
    this->fileListWidget->setCursor(Qt::PointingHandCursor);
    this->fileListWidget->setSpacing(5);
    this->fileNewButton=new QPushButton("New File");
    this->fileOpenButton=new QPushButton("Open File");
}

void DevelopWidget::setupLayouts(){
    QVBoxLayout* vLayout=new QVBoxLayout();
    vLayout->addWidget(this->fileLabel);
    vLayout->addWidget(this->fileListWidget);

    QHBoxLayout* hLayout=new QHBoxLayout();
    hLayout->addWidget(this->fileNewButton);
    hLayout->addWidget(this->fileOpenButton);

    vLayout->addLayout(hLayout);
    this->setLayout(vLayout);
}

void DevelopWidget::setupActions(){
    TabWidget* tabWidget=TabWidget::getTabWidget();
    QObject::connect(this->fileNewButton,SIGNAL(clicked()),tabWidget,SLOT(newFile()));
    QObject::connect(this->fileOpenButton,SIGNAL(clicked()),tabWidget,SLOT(openFile()));
    QObject::connect(this->fileListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onOpenRecentFile(QListWidgetItem*)));
}

void DevelopWidget::onOpenRecentFile(QListWidgetItem* listItem){
    QString path=listItem->text();
    TabWidget* tabWidget=TabWidget::getTabWidget();
    tabWidget->openFile(path);
}

void DevelopWidget::initRecentFiles(){
    RecentFile* recentFile=RecentFile::getRecentFile();
    QList<QString> fileList=recentFile->getAllFiles();
    for(int i=0;i<fileList.size()&&i<10;i++){
        QString name=fileList.at(i);
        QListWidgetItem* item=new QListWidgetItem(name);
        int index=name.lastIndexOf('.');
        QString suffix="txt";
        if(index!=-1){
            suffix=name.mid(name.lastIndexOf('.')+1);
        }
        item->setIcon(CodeTreeWidget::getIcon(suffix));
        this->fileListWidget->addItem(item);
    }
}
