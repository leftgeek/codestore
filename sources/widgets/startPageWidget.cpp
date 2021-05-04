#include "./headers/startPageWidget.h"
StartPageWidget::StartPageWidget(QWidget *parent):QWidget(parent){
    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();
}

StartPageWidget::~StartPageWidget(){

}

void StartPageWidget::changePage(QListWidgetItem *current, QListWidgetItem *previous){
    if (!current){
        current = previous;
    }

    this->stackedWidget->setCurrentIndex(this->listWidget->row(current));
}

void StartPageWidget::setupWidgets(){
    this->developWidget=new DevelopWidget();
    this->personalCenterWidget=new PersonalCenterWidget();
    this->newsWidget=new NewsWidget();

    this->listWidget = new QListWidget;
    this->listWidget->setViewMode(QListView::IconMode);
    this->listWidget->setIconSize(QSize(96, 96));
    this->listWidget->setMovement(QListView::Static);
    this->listWidget->setMaximumWidth(148);
    this->listWidget->setSpacing(15);

    this->stackedWidget = new QStackedWidget;
    this->stackedWidget->addWidget(this->developWidget);
    this->stackedWidget->addWidget(this->personalCenterWidget);
    this->stackedWidget->addWidget(this->newsWidget);

    QListWidgetItem* developButton = new QListWidgetItem(this->listWidget);
    developButton->setIcon(QIcon(":/icon/page/page_develop"));
    developButton->setText(tr("Develop"));
    developButton->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* pcButton = new QListWidgetItem(this->listWidget);
    pcButton->setIcon(QIcon(":/icon/page/page_personalcenter"));
    pcButton->setText(tr("Personal Center"));
    pcButton->setTextAlignment(Qt::AlignHCenter);

    QListWidgetItem* newsButton = new QListWidgetItem(this->listWidget);
    newsButton->setIcon(QIcon(":/icon/page/page_news"));
    newsButton->setText(tr("News"));
    newsButton->setTextAlignment(Qt::AlignHCenter);
}

void StartPageWidget::setupLayouts(){

    this->listWidget->setCurrentRow(0);
    QHBoxLayout* horizontalLayout = new QHBoxLayout;
    horizontalLayout->addWidget(this->listWidget);
    horizontalLayout->addWidget(this->stackedWidget);

    this->setLayout(horizontalLayout);
}

void StartPageWidget::setupActions(){
    connect(this->listWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changePage(QListWidgetItem*,QListWidgetItem*)));
}
