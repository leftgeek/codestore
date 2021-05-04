#ifndef IMPORTFILEWIDGET_H
#define IMPORTFILEWIDGET_H
#include "./headers/codePropertyWidget.h"
class ImportFileWidget:public CodePropertyWidget{
    Q_OBJECT
private slots:
    void onConfirm();
    void onCancel();
public:
    ImportFileWidget(QWidget* parent=0);
    ~ImportFileWidget();
    //CodeModel* getCodeModel();
};

#endif // IMPORTFILEWIDGET_H
