#ifndef MODIFYPASSWORD_H
#define MODIFYPASSWORD_H
#include <QtGui>
class ModifyPasswordWidget:public QDialog{
    Q_OBJECT
private:
    QLabel* usernameLabel;
    QLabel* oldPasswordLabel;
    QLabel* newPasswordLabel;
    QLabel* confirmPasswordLabel;
    QLabel* messageLabel;
    QLineEdit* usernameLineEdit;
    QLineEdit* oldPasswordLineEdit;
    QLineEdit* newPasswordLineEdit;
    QLineEdit* confirmPasswordLineEdit;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
protected slots:
    void onConfirm();
    void onCancel();
public:
    ModifyPasswordWidget(QWidget* parent=0);
    ~ModifyPasswordWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void showMessage(QString message);
};
#endif // MODIFYPASSWORD_H
