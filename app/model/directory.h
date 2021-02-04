#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QDir>

class Directory : public QDir
{
public:
    enum IndexingStrategy {
        INCLUDE,
        EXCLUDE
    };

    IndexingStrategy strategy;

    Directory(QString path, IndexingStrategy strategy);

    bool equal(const Directory& dir) const;
    bool operator== (const Directory& dir) const;
};

#endif // DIRECTORY_H
