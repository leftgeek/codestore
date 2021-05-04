#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H
#include <QtGui>
class RegisterWidget:public QDialog{
    Q_OBJECT
private:
    QLabel* usernameLabel;
    QLabel* passwordLabel;
    QLabel* confirmPasswordLabel;
    QLabel* emailLabel;
    QLabel* messageLabel;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QLineEdit* confirmPasswordLineEdit;
    QLineEdit* emailLineEdit;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
protected slots:
    void onConfirm();
    void onCancel();
public:
    RegisterWidget(QWidget* parent=0);
    ~RegisterWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void showMessage(QString message);
};

#endif // REGISTERWIDGET_H
