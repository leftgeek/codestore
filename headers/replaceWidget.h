#ifndef REPLACEWIDGET_H
#define REPLACEWIDGET_H
#include <QtGui>
class ReplaceWidget:public QDialog{
    Q_OBJECT
private:
    QLabel* findLabel;
    QLabel* replaceLabel;
    QLineEdit* findLineEdit;
    QLineEdit* replaceLineEdit;
    QCheckBox* findBackwardCheckBox;
    QCheckBox* findCaseSensitiveCheckBox;
    QCheckBox* findWholeWordsCheckBox;
    QPushButton* findButton;
    QPushButton* replaceButton;
    QPlainTextEdit* textEditor;
    ReplaceWidget(QWidget* parent=0);
    static ReplaceWidget* replaceWidget;
private slots:
    void onFind();
    void onReplace();
public:
    ~ReplaceWidget();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
    void setTextEditor(QPlainTextEdit* textEditor);
    static ReplaceWidget* getReplaceWidget();
};

#endif // REPLACEWIDGET_H
