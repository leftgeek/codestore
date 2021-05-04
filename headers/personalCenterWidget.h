#ifndef PERSONALCENTERWIDGET_H
#define PERSONALCENTERWIDGET_H
#include <QtGui>
class PersonalCenterWidget:public QWidget{
    Q_OBJECT
private:
    QLabel* fileLabel;
    QListWidget* fileListWidget;
    QPushButton* registerButton;
    QPushButton* loginButton;
    QPushButton* modifyPasswordButton;
    QPushButton* findPasswordButton;
private slots:
    void onRegister();
    void onLogin();
    void onModifyPassword();
    void onFindPassword();
public:
    PersonalCenterWidget(QWidget* parent=0);
    ~PersonalCenterWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
};

#endif // PERSONALCENTERWIDGET_H
