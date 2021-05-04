#ifndef LOGTREE_H
#define LOGTREE_H
#include <QDomDocument>
//
class LogTree{
private:
    QString filePath;
    QDomDocument* domDocument;
    static LogTree* logTree;
    LogTree();
public:
    void initLogTree();
    bool openFile(QString filePath);
    bool saveFile(QString filePath);
    bool saveFile();
    ~LogTree();
    static LogTree* getLogTree();
    QDomDocument* getDomDocument();
    bool addLog(QString type,int id);
    bool syncLog(int userId);
};
#endif // LOGTREE_H
