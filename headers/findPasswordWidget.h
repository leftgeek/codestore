#ifndef FINDPASSWORDWIDGET_H
#define FINDPASSWORDWIDGET_H
#include <QtGui>
class FindPasswordWidget:public QDialog{
    Q_OBJECT
private:
    QLabel* emailLabel;
    QLabel* messageLabel;
    QLineEdit* emailLineEdit;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
protected slots:
    void onConfirm();
    void onCancel();
public:
    FindPasswordWidget(QWidget* parent=0);
    ~FindPasswordWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void showMessage(QString message);
};
#endif // FINDPASSWORDWIDGET_H
