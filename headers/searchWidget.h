#ifndef SEARCH_H
#define SEARCH_H
#include <QtGui>
#include "./headers/code.h"
class SearchWidget:public QWidget{
    Q_OBJECT
private:
    QLineEdit* searchLineEdit;
    QComboBox* searchTypeComboBox;
    QPushButton* searchButton;
    QPushButton* previousButton;
    QPushButton* nextButton;
    QListWidget* listWidget;
    QList<CodeModel*> codes;
    int pageNow;
private slots:
    void onSearch();
    void onPrevious();
    void onNext();
    void onViewFile(QModelIndex index);
public:
    SearchWidget(QWidget* parent=0);
    ~SearchWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
};

#endif // SEARCH_H
