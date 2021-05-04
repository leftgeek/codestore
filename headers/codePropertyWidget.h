#ifndef CODEPROPERTYWIDGET_H
#define CODEPROPERTYWIDGET_H
#include <QtGui>
#include "./headers/code.h"
//属性类，用来显示文件的属性
class CodePropertyWidget:public QDialog{
    Q_OBJECT
protected:
    QLabel* nameLabel;
    QLabel* categoryLabel;
    QLabel* descriptionLabel;
    QLabel* shareStatusLabel;
    QLineEdit* nameLineEdit;
    QComboBox* categoryTree;
    QTextEdit* descriptionTextEdit;
    QCheckBox* shareStatusCheckBox;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    CodeModel* codeModel;
protected slots:
    virtual void onConfirm();
    virtual void onCancel();
public:
    CodePropertyWidget(QWidget* parent=0);
    ~CodePropertyWidget();
    virtual void setupWidgets();
    virtual void setupLayouts();
    virtual void setupActions();
    virtual void setCategory(QString category);
    void showProperty(CodeModel* codeModel);
};
#endif // CODEPROPERTYWIDGET_H
