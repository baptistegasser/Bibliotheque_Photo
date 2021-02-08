#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QDir>

class Directory : public QDir
{
public:
    static Directory INVALID;

    enum IndexingStrategy {
        INCLUDE,
        EXCLUDE
    };

    QString parentDirPath;
    IndexingStrategy strategy;

    Directory();
    Directory(QString path, IndexingStrategy strategy);
    bool isParentDir();

    bool equal(const Directory& dir) const;
    bool operator== (const Directory& dir) const;
};

#endif // DIRECTORY_H
