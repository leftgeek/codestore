#ifndef RECENTFILE_H
#define RECENTFILE_H
#include <QDomDocument>
//
class RecentFile{
private:
    QString filePath;
    QDomDocument* domDocument;
    static RecentFile* recentFile;
    RecentFile();
public:
    ~RecentFile();
    void initRecentFile();
    bool openFile(QString filePath);
    bool saveFile(QString filePath);
    bool saveFile();
    bool addFile(QString filePath);
    bool removeFile(QString filePath);
    QList<QString> getAllFiles();
    static RecentFile* getRecentFile();
    QDomDocument* getDomDocument();
};
#endif // RECENTFILE_H
