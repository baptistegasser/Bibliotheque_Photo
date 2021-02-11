#ifndef DIRINDEXER_H
#define DIRINDEXER_H

#include "model/directory.h"
#include "QFileInfo"
#include <QFuture>

#include <QObject>

class DirIndexer : public QObject
{
    Q_OBJECT

private:
    int fileToIndex;
    int indexedFiles;
    Directory dirToIndex;
    QDir::Filters indexFilters;
    QList<QString> supportedFilesExtentions;
    QFuture<QList<Directory>> future;

    QList<Directory> index();
    void findFilesToIndex();
    void indexDir(Directory &dir, QList<Directory> *indexedDirs);
    void indexImage(const Directory &parent, const QFileInfo &infos);

public:
    explicit DirIndexer(Directory dir, QObject *parent = nullptr);
    void startIndexing();
    QList<Directory> getResult() const;

signals:
    void doneIndexing();
    void fileToIndexChanged(int count);
    void indexedFilesChanged(int count);
};

#endif // DIRINDEXER_H
