#include <QtGui>
#include "./headers/textEditor.h"
#include "./headers/recentFile.h"
TextEditor::TextEditor(QWidget* parent):QPlainTextEdit(parent){
    this->setupWidgets();
    this->setupActions();
}

TextEditor::~TextEditor(){

}

void TextEditor::setupWidgets(){
    this->lineNumberArea = new LineNumberArea(this);
    this->setViewportMargins(30, 0, 0, 0);
    this->highlighter=NULL;

}

void TextEditor::setupActions(){
    QObject::connect(this,SIGNAL(copyAvailable(bool)),this,SLOT(onCopyAvailable(bool)));
}

void TextEditor::setFilePath(QString filePath){
    this->filePath=filePath;
}

QString TextEditor::getFilePath(){
    return this->filePath;
}

void TextEditor::onUndoAvailable(bool isUndo){
    this->isUndo=isUndo;
}

void TextEditor::onRedoAvailable(bool isRedo){
    this->isRedo=isRedo;
}

void TextEditor::onCopyAvailable(bool isCopy){
    this->isCopy=isCopy;
}

bool TextEditor::newFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)){
        file.close();
        result=this->openFile(filePath);
    }else{
        QMessageBox::warning(this, this->filePath,"The document can not ben created!",QMessageBox::Ok);
    }
    return result;
}

bool TextEditor::openFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);
        QString content = in.readAll();
        this->setPlainText(content);
        file.close();
        result=true;
        this->filePath=filePath;
        this->document()->setModified(false);
        this->document()->setDefaultFont(QFont("Monospace",11,QFont::Normal));
        this->isUndo=false;
        this->isRedo=false;
        this->isCopy=false;
        QObject::connect(this->document(),SIGNAL(undoAvailable(bool)),this,SLOT(onUndoAvailable(bool)));
        QObject::connect(this->document(),SIGNAL(redoAvailable(bool)),this,SLOT(onRedoAvailable(bool)));
        connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
        connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
        QString fileType="txt";
        int index=this->filePath.lastIndexOf('.');
        if(index!=-1){
            fileType=this->filePath.mid(index+1);
        }
        this->highlighter=new Highlighter(this->document());
        this->highlighter->initHighlighter(fileType);
        highlightCurrentLine();

        //
        RecentFile* recentFile=RecentFile::getRecentFile();
        recentFile->addFile(filePath);
    }else{
        QMessageBox::warning(this, this->filePath,"The document can not be opened!",QMessageBox::Ok);
    }
    return result;
}

bool TextEditor::saveFile(QString filePath){
    bool result=false;
    QFile* file=new QFile(filePath);
    if(file->open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(file);
        out<<this->document()->toPlainText();
        file->close();
        this->document()->setModified(false);
        result=true;
    }else{
        QMessageBox::warning(this, this->filePath,"The document can not be saved!",QMessageBox::Ok);
    }
    return result;
}
bool TextEditor::closeFile(){
    bool result=true;
    if(this->document()->isModified()){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, this->filePath,
                     tr("The document has been modified.\n"
                        "Do you want to save your changes?"),
                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save){
            this->saveFile(this->filePath);
        }else if (ret == QMessageBox::Cancel){
            result=false;
        }
    }
    return result;
}

bool TextEditor::canUndo(){
    return this->isUndo;
}

bool TextEditor::canRedo(){
    return this->isRedo;
}

bool TextEditor::canCopy(){
    return this->isCopy;
}

void TextEditor::keyPressEvent(QKeyEvent * event){
    switch(event->key()){
    case Qt::Key_Tab:
        this->insertPlainText("    ");//insert 4 space instead of tab
        break;
    default:
        QPlainTextEdit::keyPressEvent(event);
        break;
    }

}

void TextEditor::updateLineNumberArea(const QRect &rect, int dy){
    if (dy){
        lineNumberArea->scroll(0, dy);
    }
    else{
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }
}

void TextEditor::resizeEvent(QResizeEvent *e){
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), 30, cr.height()));
}

void TextEditor::highlightCurrentLine(){
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor(200,120,120,100);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = this->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void TextEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor(200,200,200,200));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.setPen(QColor(64,64,64));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }
}

void TextEditor::changeHighlightMode(QString fileType){
    if(this->highlighter==NULL){
        this->highlighter=new Highlighter(this->document());
    }
    this->highlighter->initHighlighter(fileType);
}
