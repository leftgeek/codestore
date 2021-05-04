#ifndef NEWFILEWIDGET_H
#define NEWFILEWIDGET_H
#include "./headers/codePropertyWidget.h"
class NewFileWidget:public CodePropertyWidget{
    Q_OBJECT
private slots:
    void onConfirm();
    void onCancel();
public:
    NewFileWidget(QWidget* parent=0);
    ~NewFileWidget();
    CodeModel* getCodeModel();
};

#endif // NEWFILEWIDGET_H
