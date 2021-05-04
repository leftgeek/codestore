#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H
#include <QtGui>
class LoginWidget:public QDialog{
    Q_OBJECT
private:
    QLabel* usernameLabel;
    QLabel* passwordLabel;
    QLabel* messageLabel;
    QLineEdit* usernameLineEdit;
    QLineEdit* passwordLineEdit;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
protected slots:
    void onConfirm();
    void onCancel();
public:
    LoginWidget(QWidget* parent=0);
    ~LoginWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void showMessage(QString message);
};

#endif // LOGINWIDGET_H
