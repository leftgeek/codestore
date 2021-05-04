#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H
#include <QSyntaxHighlighter>
#include <QDomDocument>
#include <QHash>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:
    Highlighter(QTextDocument *parent = 0);
    ~Highlighter();
    bool openFile(QString filePath);
    void initKeywords();
    void initRules();
    void initHighlighter(QString fileType);
protected:
    void highlightBlock(const QString &text);

private:
    struct HighlightingRule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
    QDomDocument domDocument;
    QStringList keywordPatterns;
};

#endif // HIGHLIGHTER_H
