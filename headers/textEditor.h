#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H
#include <QPlainTextEdit>
#include "./headers/highlighter.h"
class LineNumberArea;

class TextEditor:public QPlainTextEdit{
    Q_OBJECT
private:
    QString filePath;//文件路径
    bool isUndo;
    bool isRedo;
    bool isCopy;
    Highlighter* highlighter;
    QWidget *lineNumberArea;
protected:
    void resizeEvent(QResizeEvent *event);
protected slots:
    void onUndoAvailable(bool isUndo);
    void onRedoAvailable(bool isRedo);
    void onCopyAvailable(bool isCopy);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &, int);
public:
    TextEditor(QWidget* parent=0);
    ~TextEditor();
    void setupWidgets();
    void setupActions();
    void setFilePath(QString filePath);
    QString getFilePath();
    bool newFile(QString filePath);
    bool openFile(QString filePath);
    bool saveFile(QString filePath);
    bool closeFile();
    bool canUndo();
    bool canRedo();
    bool canCopy();
    void keyPressEvent(QKeyEvent *);//键盘按下事件函数
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    void changeHighlightMode(QString fileType);

};
class LineNumberArea : public QWidget{
private:
    TextEditor* textEditor;
protected:
    void paintEvent(QPaintEvent *event) {
        this->textEditor->lineNumberAreaPaintEvent(event);
    }
public:
    LineNumberArea(TextEditor* textEditor) : QWidget(textEditor) {
        this->textEditor = textEditor;
    }
};
#endif // TEXTEDITOR_H
