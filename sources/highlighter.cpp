#include <QtGui>
#include "./headers/highlighter.h"

Highlighter::Highlighter(QTextDocument *parent):QSyntaxHighlighter(parent){

}

Highlighter::~Highlighter(){

}

void Highlighter::initKeywords(){
    QDomElement rootElement=this->domDocument.firstChildElement("keywords");
    QDomNodeList nodeList=rootElement.childNodes();
    for(int i=0;i<nodeList.size();i++){
        QDomElement keywordElement=nodeList.at(i).toElement();
        QString keyword="\\b"+keywordElement.text()+"\\b";
        this->keywordPatterns<<keyword;
    }
}

void Highlighter::initRules (){
    this->highlightingRules.clear();
    HighlightingRule rule;
    keywordFormat.setForeground(QColor(220,120,100,220));
    keywordFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, this->keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        highlightingRules.append(rule);
    }

    singleLineCommentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRules.append(rule);

    multiLineCommentFormat.setForeground(Qt::darkGreen);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegExp("\".*\"");
    rule.format = quotationFormat;
    highlightingRules.append(rule);

    functionFormat.setForeground(Qt::blue);
    rule.pattern = QRegExp("\\b[A-Za-z_][A-Za-z_0-9]*(?=[\\s]*\\()");
    rule.format = functionFormat;
    highlightingRules.append(rule);

    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

bool Highlighter::openFile(QString filePath){
    bool result=false;
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        this->domDocument.setContent(&file);
        file.close();
        result=true;
    }
    return result;
}

void Highlighter::initHighlighter(QString fileType){
    if(fileType.length()>0){
        QString filePath="syntax/"+fileType.toLower()+".xml";
        if(this->openFile(filePath)){
            this->initKeywords();   
        }
        this->initRules();
    }
}

void Highlighter::highlightBlock(const QString &text)
{
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = commentStartExpression.indexIn(text);

    while (startIndex >= 0) {

        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
    }
}
