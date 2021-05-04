#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "./headers/tabWidget.h"
#include "./headers/codeTreeWidget.h"
#include "./headers/propertyWidget.h"
#include "./headers/replaceWidget.h"
#include "./headers/startPageWidget.h"
#include "./headers/user.h"
#include "./headers/sync.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu* fileMenu;
    QMenu* editMenu;
    QMenu* viewMenu;
    QMenu* viewHighlightMode;
    QMenu* toolMenu;
    QMenu* helpMenu;
    QMenu* fileNewMenu;
    QMenu* codeTreeMenu;
    QMenu* codeTreeNewMenu;
    QAction* fileNew;
    QAction* categoryNew;
    QAction* fileOpen;
    QAction* fileImport;
    QAction* fileSave;
    QAction* fileSaveAs;
    QAction* fileClose;
    QAction* fileQuit;
    QAction* treeFileOpen;
    QAction* fileRename;
    QAction* fileDelete;
    QAction* fileProperty;
    QAction* editUndo;
    QAction* editRedo;
    QAction* editCut;
    QAction* editCopy;
    QAction* editPaste;
    QAction* editSelectAll;
    QAction* viewToolBar;
    QAction* viewStatusBar;
    QAction* viewCategory;
    QAction* viewProperty;
    QAction* viewStartPage;
    QAction* viewHighlightModeC;
    QAction* viewHighlightModeCPP;
    QAction* viewHighlightModeJAVA;
    QAction* toolFind;
    QAction* toolSearch;
    QAction* toolSync;
    QAction* toolOptions;
    QAction* helpAbout;
    QAction* helpContent;
    QToolBar* toolBar;

    QLabel* cursorPositionLabel;
    TabWidget* tabWidget;
    UserModel* userModel;
    TextEditor* currentTextEditor;//当前文本编辑器
    CodeTreeWidget* codeTreeWidget;//显示代码结构控件
    CodeTree* codeTree;//
    Sync* sync;
    PropertyWidget* propertyWidget;//文件属性
    ReplaceWidget* replaceWidget;//查找与替换
    StartPageWidget* startPageWidget;//
private slots:
    void onFileNew();
    void onFileOpen();
    void onFileImport();
    void onFileSave();
    void onFileSaveAs();
    void onFileClose();
    void onFileQuit();
    void onTreeFileOpen();
    void onCategoryNew();
    void onFileRename();
    void onFileDelete();
    void onFileProperty();
    void onEditUndo();
    void onEditRedo();
    void onEditCut();
    void onEditCopy();
    void onEditPaste();
    void onEditSelectAll();
    void onViewToolBar();
    void onViewStatusBar();
    void onViewCategory();
    void onViewProperty();
    void onViewStartPage();
    void onViewHighlightModeC();
    void onViewHighlightModeCPP();
    void onViewHighlightModeJAVA();
    void onToolFind();
    void onToolSearch();
    void onToolSync();
    void onToolOptions();
    void onHelpAbout();
    void onHelpContent();

    void onItemPressed(QTreeWidgetItem *item, int column);
    void onTabChanged(int index);
    void onModified();
    void onCursorPositionChanged();
protected:
    void closeEvent(QCloseEvent *event);
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setupWidgets();
    void setupLayouts();
    void setupActions();
};

#endif // MAINWINDOW_H
