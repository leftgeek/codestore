#include "./headers/mainWindow.h"
#include "./headers/newFileWidget.h"
#include "./headers/newCategoryWidget.h"
#include "./headers/helpWidget.h"
#include "./headers/categoryPropertyWidget.h"
#include "./headers/codePropertyWidget.h"
#include "./headers/searchWidget.h"
#include "./headers/loginWidget.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){

    this->setupWidgets();
    this->setupLayouts();
    this->setupActions();

    //initialize
    this->sync->autoLogin();
    this->onViewStartPage();
}

MainWindow::~MainWindow(){
    if(this->tabWidget!=NULL){
        delete(this->tabWidget);
    }

    if(this->codeTree!=NULL){
        delete(this->codeTree);
    }

    if(this->sync!=NULL){
        delete(this->sync);
    }

    if(this->codeTreeWidget!=NULL){
        delete(this->codeTreeWidget);
    }

    if(this->replaceWidget!=NULL){
        delete(this->replaceWidget);
    }
}

void MainWindow::setupWidgets(){
    this->setWindowTitle("CodeSync");
    this->fileNew = new QAction(QIcon(":icon/file/file_new"), "&File", this);
    this->fileNew->setShortcut(QKeySequence::New);
    this->categoryNew = new QAction("&Category", this);
    this->fileOpen = new QAction(QIcon(":icon/file/file_open"),"&Open", this);
    this->fileOpen->setShortcut(QKeySequence::Open);
    this->fileImport = new QAction("&Import", this);
    this->fileSave = new QAction(QIcon(":icon/file/file_save"),"&Save", this);
    this->fileSave->setShortcut(QKeySequence::Save);
    this->fileSaveAs = new QAction(QIcon(":icon/file/file_saveas"),"Save &As...", this);
    this->fileSaveAs->setShortcut(QKeySequence::SaveAs);
    this->fileClose = new QAction(QIcon(":icon/file/file_quit"),"&Close", this);
    this->fileClose->setShortcut(QKeySequence::Close);
    this->fileQuit = new QAction(QIcon(":icon/file/file_quit"),"&Quit", this);
    this->fileQuit->setShortcut(QKeySequence::Quit);
    this->treeFileOpen = new QAction("&Open", this);
    this->fileRename = new QAction("&Rename", this);
    this->fileDelete = new QAction("&Delete", this);
    this->fileProperty = new QAction("&Property", this);

    this->editUndo = new QAction(QIcon(":icon/edit/edit_undo"),"&Undo", this);
    this->editUndo->setShortcut(QKeySequence::Undo);
    this->editRedo = new QAction(QIcon(":icon/edit/edit_redo"),"&Redo", this);
    this->editRedo->setShortcut(QKeySequence::Redo);
    this->editCut = new QAction(QIcon(":icon/edit/edit_cut"),"Cu&t", this);
    this->editCut->setShortcut(QKeySequence::Cut);
    this->editCopy = new QAction(QIcon(":icon/edit/edit_copy"),"&Copy", this);
    this->editCopy->setShortcut(QKeySequence::Copy);
    this->editPaste = new QAction(QIcon(":icon/edit/edit_paste"),"&Paste", this);
    this->editPaste->setShortcut(QKeySequence::Cut);
    this->editSelectAll = new QAction("Select &All", this);
    this->editSelectAll->setShortcut(QKeySequence::SelectAll);

    this->viewToolBar = new QAction("&Toolbar", this);
    this->viewToolBar->setCheckable(true);
    this->viewToolBar->setChecked(true);
    this->viewStatusBar = new QAction("&Statusbar", this);
    this->viewStatusBar->setCheckable(true);
    this->viewStatusBar->setChecked(true);
    this->viewCategory = new QAction("&Category", this);
    this->viewProperty = new QAction("&Property", this);
    this->viewStartPage = new QAction("St&art page", this);
    this->viewHighlightModeC = new QAction("&C", this);
    this->viewHighlightModeCPP = new QAction("C++", this);
    this->viewHighlightModeJAVA = new QAction("&Java", this);

    this->toolFind = new QAction("&Find/Replace", this);
    this->toolFind->setShortcut(QKeySequence::Find);
    this->toolSearch = new QAction("&Search", this);
    this->toolSync = new QAction("S&ync", this);
    this->toolOptions = new QAction("&Options", this);

    this->helpContent = new QAction("&Contents", this);
    this->helpAbout = new QAction("&About", this);

    this->cursorPositionLabel=new QLabel();

    this->tabWidget=TabWidget::getTabWidget();
    this->codeTree=CodeTree::getCodeTree();
    this->sync=Sync::getSync();
    this->codeTreeWidget=CodeTreeWidget::getCodeTreeWidget();
    this->propertyWidget=new PropertyWidget();
    this->replaceWidget=ReplaceWidget::getReplaceWidget();

}

void MainWindow::setupLayouts(){
    QMenuBar* menus = this->menuBar();
    this->fileMenu = menus->addMenu("&File");
    this->fileNewMenu = this->fileMenu->addMenu("&New");
    this->fileNewMenu->addAction(this->fileNew);
    this->fileNewMenu->addAction(this->categoryNew);
    this->fileMenu->addAction(this->fileOpen);
    this->fileMenu->addAction(this->fileImport);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->fileSave);
    this->fileMenu->addAction(this->fileSaveAs);
    this->fileMenu->addSeparator();
    this->fileMenu->addAction(this->fileClose);
    this->fileMenu->addAction(this->fileQuit);

    this->editMenu = menus->addMenu("&Edit");
    this->editMenu->addAction(this->editUndo);
    this->editMenu->addAction(this->editRedo);
    this->editMenu->addSeparator();
    this->editMenu->addAction(this->editCut);
    this->editMenu->addAction(this->editCopy);
    this->editMenu->addAction(this->editPaste);
    this->editMenu->addSeparator();
    this->editMenu->addAction(this->editSelectAll);

    this->viewMenu = menus->addMenu("&View");
    this->viewMenu->addAction(this->viewToolBar);
    this->viewMenu->addAction(this->viewStatusBar);
    this->viewMenu->addAction(this->viewCategory);
    this->viewMenu->addAction(this->viewProperty);
    this->viewMenu->addAction(this->viewStartPage);
    this->viewMenu->addSeparator();
    this->viewHighlightMode = this->viewMenu->addMenu("&Highlight Mode");
    this->viewHighlightMode->addAction(this->viewHighlightModeC);
    this->viewHighlightMode->addAction(this->viewHighlightModeCPP);
    this->viewHighlightMode->addAction(this->viewHighlightModeJAVA);

    this->toolMenu = menus->addMenu("&Tool");
    this->toolMenu->addAction(this->toolFind);
    this->toolMenu->addAction(this->toolSearch);
    this->toolMenu->addSeparator();
    this->toolMenu->addAction(this->toolSync);
    this->toolMenu->addAction(this->toolOptions);

    this->helpMenu = menus->addMenu("&Help");
    this->helpMenu->addAction(this->helpContent);
    this->helpMenu->addSeparator();
    this->helpMenu->addAction(this->helpAbout);

    this->codeTreeMenu = new QMenu();
    this->codeTreeNewMenu = this->codeTreeMenu->addMenu("&New");
    this->codeTreeNewMenu->addAction(this->fileNew);
    this->codeTreeNewMenu->addAction(this->categoryNew);
    this->codeTreeMenu->addAction(this->treeFileOpen);
    this->codeTreeMenu->addAction(this->fileRename);
    this->codeTreeMenu->addAction(this->fileDelete);
    this->codeTreeMenu->addAction(this->fileProperty);

    this->toolBar = this->addToolBar("Standard");
    toolBar->addAction(this->fileNew);
    toolBar->addAction(this->fileOpen);
    toolBar->addSeparator();
    toolBar->addAction(this->fileSave);
    toolBar->addAction(this->fileSaveAs);
    toolBar->addSeparator();
    toolBar->addAction(this->editUndo);
    toolBar->addAction(this->editRedo);
    toolBar->addSeparator();
    toolBar->addAction(this->editCopy);
    toolBar->addAction(this->editCut);
    toolBar->addAction(this->editPaste);

    QStatusBar* status = this->statusBar();
    status->addWidget(this->cursorPositionLabel);

    QTabWidget* categoryTab=new QTabWidget();
    categoryTab->setTabPosition(QTabWidget::South);
    categoryTab->addTab(this->codeTreeWidget,"Category");
    this->codeTreeWidget->expandAll();

    QTabWidget* propertyTab=new QTabWidget();
    propertyTab->setTabPosition(QTabWidget::South);
    propertyTab->addTab(this->propertyWidget,"Property");

    QSplitter* hSplitter=new QSplitter();
    hSplitter->addWidget(categoryTab);
    hSplitter->addWidget(this->tabWidget);
    hSplitter->addWidget(propertyTab);
    QList<int> hList;
    hList.append(200);
    hList.append(600);
    hList.append(200);
    hSplitter->setSizes(hList);

    this->setCentralWidget(hSplitter);

}

void MainWindow::setupActions(){

    this->editCopy->setEnabled(false);
    this->editCut->setEnabled(false);
    this->editUndo->setEnabled(false);
    this->editRedo->setEnabled(false);
    this->editPaste->setEnabled(false);
    this->editSelectAll->setEnabled(false);
    this->fileSave->setEnabled(false);
    this->fileSaveAs->setEnabled(false);
    this->fileClose->setEnabled(false);
    this->viewHighlightMode->setEnabled(false);
    this->toolFind->setEnabled(false);
    this->propertyWidget->setVisible(true);
    QObject::connect(this->fileNew, SIGNAL(triggered()), this, SLOT(onFileNew()));
    QObject::connect(this->fileImport, SIGNAL(triggered()), this, SLOT(onFileImport()));
    QObject::connect(this->fileOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
    QObject::connect(this->fileSave, SIGNAL(triggered()), this, SLOT(onFileSave()));
    QObject::connect(this->fileSaveAs, SIGNAL(triggered()), this, SLOT(onFileSaveAs()));
    QObject::connect(this->fileClose, SIGNAL(triggered()), this, SLOT(onFileClose()));
    QObject::connect(this->fileQuit, SIGNAL(triggered()), this, SLOT(onFileQuit()));

    QObject::connect(this->codeTreeWidget,SIGNAL(itemPressed(QTreeWidgetItem*,int)),this,SLOT(onItemPressed(QTreeWidgetItem*,int)));
    QObject::connect(this->codeTreeWidget,SIGNAL(doubleClicked(QModelIndex)),this,SLOT(onTreeFileOpen()));
    QObject::connect(this->categoryNew,SIGNAL(triggered()),this,SLOT(onCategoryNew()));
    QObject::connect(this->treeFileOpen,SIGNAL(triggered()),this,SLOT(onTreeFileOpen()));
    QObject::connect(this->fileRename,SIGNAL(triggered()),this,SLOT(onFileRename()));
    QObject::connect(this->fileDelete,SIGNAL(triggered()),this,SLOT(onFileDelete()));
    QObject::connect(this->fileProperty,SIGNAL(triggered()),this,SLOT(onFileProperty()));

    QObject::connect(this->editUndo,SIGNAL(triggered()),this,SLOT(onEditUndo()));
    QObject::connect(this->editRedo,SIGNAL(triggered()),this,SLOT(onEditRedo()));
    QObject::connect(this->editCut,SIGNAL(triggered()),this,SLOT(onEditCut()));
    QObject::connect(this->editCopy,SIGNAL(triggered()),this,SLOT(onEditCopy()));
    QObject::connect(this->editPaste,SIGNAL(triggered()),this,SLOT(onEditPaste()));
    QObject::connect(this->editSelectAll,SIGNAL(triggered()),this,SLOT(onEditSelectAll()));

    QObject::connect(this->viewToolBar,SIGNAL(triggered()),this,SLOT(onViewToolBar()));
    QObject::connect(this->viewStatusBar,SIGNAL(triggered()),this,SLOT(onViewStatusBar()));
    QObject::connect(this->viewCategory,SIGNAL(triggered()),this,SLOT(onViewCategory()));
    QObject::connect(this->viewProperty,SIGNAL(triggered()),this,SLOT(onViewProperty()));
    QObject::connect(this->viewStartPage,SIGNAL(triggered()),this,SLOT(onViewStartPage()));

    QObject::connect(this->toolFind,SIGNAL(triggered()),this,SLOT(onToolFind()));
    QObject::connect(this->toolSearch,SIGNAL(triggered()),this,SLOT(onToolSearch()));
    QObject::connect(this->toolSync,SIGNAL(triggered()),this,SLOT(onToolSync()));
    QObject::connect(this->toolOptions,SIGNAL(triggered()),this,SLOT(onToolOptions()));

    QObject::connect(this->helpAbout, SIGNAL(triggered()), this, SLOT(onHelpAbout()));
    QObject::connect(this->helpContent,SIGNAL(triggered()),this,SLOT(onHelpContent()));

    QObject::connect(this->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(onTabChanged(int)));
}

void MainWindow::onFileNew(){
    QString categoryName="categories";
    if(this->codeTreeWidget->selectedItems().size()>0){
        QTreeWidgetItem *item=this->codeTreeWidget->selectedItems().at(0);
        categoryName=item->text(0);
    }
    this->tabWidget->newFile(categoryName);
}

void MainWindow::onFileOpen(){
    this->tabWidget->openFile();
}

void MainWindow::onFileImport(){
    QString fileFilters = tr("C files (*.c)\n"
                           "C++ files (*.cpp)\n"
                           "Java files (*.java)\n"
                           "HTML files (*.html)\n"
                           "All files (*)");
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), ".", fileFilters);
    if (!filePath.isEmpty()){

    }
}

void MainWindow::onFileSave(){
    this->tabWidget->saveFile(this->tabWidget->getCurrentTextEditor()->getFilePath());
    this->fileSave->setEnabled(false);
    this->tabWidget->setTabModified(false);
}

void MainWindow::onFileSaveAs(){
    QString fileFilters = tr("C files (*.c)\n"
                           "C++ files (*.cpp)\n"
                           "Java files (*.java)\n"
                           "HTML files (*.html)\n"
                           "All files (*)");
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save As"), this->tabWidget->getCurrentTextEditor()->getFilePath(), fileFilters);
    if (!filePath.isEmpty()){
        this->tabWidget->saveFile(filePath);
    }
}

void MainWindow::onFileClose(){
    this->tabWidget->closeFile();
}

void MainWindow::closeEvent(QCloseEvent *event){
    if(this->tabWidget->closeAllFile()){
        event->accept();
    }else{
        event->ignore();
    }
}

void MainWindow::onFileQuit(){
    this->close();
}

void MainWindow::onItemPressed(QTreeWidgetItem *item, int column){
    if (qApp->mouseButtons() == Qt::RightButton){
        this->fileProperty->setEnabled(true);
        this->fileRename->setEnabled(true);
        this->fileDelete->setEnabled(true);
        if(item->type()==0){//category
            if(item->text(0)=="categories"){//root category is readonly
                this->fileProperty->setEnabled(false);
                this->fileRename->setEnabled(false);
                this->fileDelete->setEnabled(false);
            }
            this->codeTreeNewMenu->setEnabled(true);
            this->treeFileOpen->setEnabled(false);
        }else{//code
            this->codeTreeNewMenu->setEnabled(false);
            this->treeFileOpen->setEnabled(true);
        }
        this->codeTreeMenu->exec(QCursor::pos());
    }
}

void MainWindow::onCategoryNew(){
    NewCategoryWidget newCategoryWidget;
    if(this->codeTreeWidget->selectedItems().size()>0){
        QTreeWidgetItem* item=this->codeTreeWidget->selectedItems().at(0);
        newCategoryWidget.setParentCategory(item->text(0));
    }
    if(newCategoryWidget.exec()==QDialog::Accepted){
        CategoryModel* categoryModel=newCategoryWidget.getCategoryModel();//create new category
        this->codeTreeWidget->addCategory(categoryModel);
    }
}

void MainWindow::onTreeFileOpen(){
    QTreeWidgetItem *item=this->codeTreeWidget->selectedItems().at(0);
    if(item->type()==1){//code
        QString filePath="codes/"+item->text(0);
        this->tabWidget->openFile(filePath);
    }
}

void MainWindow::onFileRename(){
    QTreeWidgetItem *item=this->codeTreeWidget->selectedItems().at(0);
}

void MainWindow::onFileDelete(){
    if(this->codeTreeWidget->selectedItems().size()>0){
        QTreeWidgetItem *item=this->codeTreeWidget->selectedItems().at(0);
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Warning", "Sure to delete "+item->text(0)+"?",QMessageBox::Ok | QMessageBox::Cancel);
        if (ret == QMessageBox::Ok){
            if(item->type()==1){//code
                QString filePath="codes/"+item->text(0);
                int index = this->tabWidget->findIndex(filePath);
                if(index!=-1){
                    this->tabWidget->removeTab(index);
                    delete(this->tabWidget->widget(index));
                }
            }
            this->codeTreeWidget->deleteItem(item);
        }
    }
}

void MainWindow::onFileProperty(){
    QTreeWidgetItem *item=this->codeTreeWidget->selectedItems().at(0);
    this->propertyWidget->setEnabled(true);
    if(item->type()==0){//category
        CategoryModel* categoryModel=this->codeTree->getCategory(item->text(0));
        if(categoryModel!=NULL){
            CategoryPropertyWidget* categoryWidget=new CategoryPropertyWidget();
            categoryWidget->showProperty(categoryModel);
            this->propertyWidget->setPropertyWidget(categoryWidget);
            this->propertyWidget->setVisible(true);
        }else{
            this->propertyWidget->setVisible(false);
        }
    }else{//code
        CodeModel* codeModel=this->codeTree->getCode(item->text(0));
        if(codeModel!=NULL){
            CodePropertyWidget* codeWidget=new CodePropertyWidget();
            codeWidget->showProperty(codeModel);
            this->propertyWidget->setPropertyWidget(codeWidget);
            this->propertyWidget->setVisible(true);
        }else{
            this->propertyWidget->setVisible(false);
        }
    }
}

void MainWindow::onEditUndo(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->document()->undo();
    }
}

void MainWindow::onEditRedo(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->document()->redo();
    }
}

void MainWindow::onEditCut(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->cut();
    }
}

void MainWindow::onEditCopy(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->copy();
    }
}

void MainWindow::onEditPaste(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->paste();
    }
}

void MainWindow::onEditSelectAll(){
    if(this->currentTextEditor!=NULL){
        this->currentTextEditor->selectAll();
    }
}

void MainWindow::onViewToolBar(){
    if(this->toolBar->isVisible()){
        this->toolBar->setVisible(false);
        this->viewToolBar->setChecked(false);
    }else{
        this->toolBar->setVisible(true);
        this->viewToolBar->setChecked(true);
    }
}

void MainWindow::onViewStatusBar(){
    if(this->statusBar()->isVisible()){
        this->statusBar()->setVisible(false);
        this->viewStatusBar->setChecked(false);
    }else{
        this->statusBar()->setVisible(true);
        this->viewStatusBar->setChecked(true);
    }
}

void MainWindow::onViewCategory(){
    this->codeTreeWidget->setFocus();
}

void MainWindow::onViewProperty(){
    this->propertyWidget->setFocus();
}

void MainWindow::onViewStartPage(){
    StartPageWidget* startPageWidget=new StartPageWidget();
    this->tabWidget->openTab(startPageWidget,"Start page");
}

void MainWindow::onViewHighlightModeC(){
    this->currentTextEditor->changeHighlightMode("c");
}

void MainWindow::onViewHighlightModeCPP(){
    this->currentTextEditor->changeHighlightMode("cpp");
}

void MainWindow::onViewHighlightModeJAVA(){
    this->currentTextEditor->changeHighlightMode("java");
}

void MainWindow::onToolFind(){
    if(this->replaceWidget->isVisible()){
        this->replaceWidget->activateWindow();
    }else{
        this->replaceWidget->setWindowFlags(Qt::WindowStaysOnTopHint);
        this->replaceWidget->setVisible(true);
        QDesktopWidget* desktop = QApplication::desktop();
        this->replaceWidget->move((desktop->width() - this->replaceWidget->width())/2, (desktop->height() - this->replaceWidget->height())/2);
    }
}

void MainWindow::onToolSearch(){
    SearchWidget* searchWidget=new SearchWidget();
    if(!this->tabWidget->openTab(searchWidget,"Search")){
        delete(searchWidget);
    }
}

void MainWindow::onToolSync(){
    if(this->sync->isLogin()){
        this->sync->syncCode();
    }else{
        LoginWidget loginWidget;
        if(loginWidget.exec()==QDialog::Accepted){
            this->sync->syncCode();
        }
    }
}

void MainWindow::onToolOptions(){

}

void MainWindow::onHelpAbout(){
    QMessageBox::about(this, tr("About"),
            tr("<h2>Code Sync 1.0</h2>"
               "<p>Copyright &copy; 2011 Software Inc."
               "<p>Code Sync is created by 余亚"));
}

void MainWindow::onHelpContent(){
    HelpWidget* helpWidget=new HelpWidget();
    if(!this->tabWidget->openTab(helpWidget,"Help")){
        delete(helpWidget);
    }
}

void MainWindow::onTabChanged(int index){
    this->currentTextEditor=this->tabWidget->getCurrentTextEditor();
    if(this->currentTextEditor!=NULL){
        QObject::connect(this->currentTextEditor,SIGNAL(copyAvailable(bool)),this->editCopy,SLOT(setEnabled(bool)));
        QObject::connect(this->currentTextEditor,SIGNAL(copyAvailable(bool)),this->editCut,SLOT(setEnabled(bool)));
        QObject::connect(this->currentTextEditor->document(),SIGNAL(undoAvailable(bool)),this->editUndo,SLOT(setEnabled(bool)));
        QObject::connect(this->currentTextEditor->document(),SIGNAL(redoAvailable(bool)),this->editRedo,SLOT(setEnabled(bool)));
        QObject::connect(this->currentTextEditor->document(),SIGNAL(contentsChanged()),this,SLOT(onModified()));
        QObject::connect(this->currentTextEditor,SIGNAL(cursorPositionChanged()),this,SLOT(onCursorPositionChanged()));

        this->onModified();
        this->fileSaveAs->setEnabled(true);
        this->fileClose->setEnabled(true);

        this->editUndo->setEnabled(this->currentTextEditor->canUndo());
        this->editRedo->setEnabled(this->currentTextEditor->canRedo());
        this->editCopy->setEnabled(this->currentTextEditor->canCopy());
        this->editCut->setEnabled(this->currentTextEditor->canCopy());
        this->editPaste->setEnabled(this->currentTextEditor->canPaste());
        this->editSelectAll->setEnabled(true);
        this->viewHighlightMode->setEnabled(true);
        this->toolFind->setEnabled(true);

        this->onCursorPositionChanged();

        this->replaceWidget->setTextEditor(this->currentTextEditor);
        this->propertyWidget->setVisible(true);

        //property is changed when tab changed
        QString codeName=this->currentTextEditor->getFilePath().mid(this->currentTextEditor->getFilePath().lastIndexOf("/")+1);
        CodeModel* codeModel=this->codeTree->getCode(codeName);
        if(codeModel!=NULL){
            CodePropertyWidget* codeWidget=new CodePropertyWidget();
            codeWidget->showProperty(codeModel);
            this->propertyWidget->setPropertyWidget(codeWidget);
        }
    }else{
        this->fileSave->setEnabled(false);
        this->fileSaveAs->setEnabled(false);
        this->fileClose->setEnabled(false);

        this->editCopy->setEnabled(false);
        this->editCut->setEnabled(false);
        this->editUndo->setEnabled(false);
        this->editRedo->setEnabled(false);
        this->editPaste->setEnabled(false);
        this->editSelectAll->setEnabled(false);
        this->viewHighlightMode->setEnabled(false);
        this->toolFind->setEnabled(false);

        this->cursorPositionLabel->setText("");
        this->replaceWidget->setVisible(false);
        this->propertyWidget->setVisible(false);
    }
}

void MainWindow::onModified(){
    if(this->currentTextEditor->document()->isModified()){
        this->fileSave->setEnabled(true);
        this->tabWidget->setTabModified(true);
    }else{
        this->fileSave->setEnabled(false);
        this->tabWidget->setTabModified(false);
    }
}

void MainWindow::onCursorPositionChanged(){
    QTextCursor textCursor=this->currentTextEditor->textCursor();
    int row = textCursor.blockNumber()+1;
    int col = textCursor.columnNumber()+1;
    QString position="Line:"+QString::number(row)+",Col:"+QString::number(col);
    this->cursorPositionLabel->setText(position);
}


