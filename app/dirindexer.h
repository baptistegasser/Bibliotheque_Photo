#ifndef DIRINDEXER_H
#define DIRINDEXER_H

#include "model/directory.h"
#include "QFileInfo"

class DirIndexer
{
public:
    DirIndexer(Directory dir);
    QList<Directory> index();  // Index the dirToIndex and return all indexed subdirs

private:
    Directory dirToIndex;
    QDir::Filters indexFilters;
    void indexDir(Directory &dir, QList<Directory> *indexedDirs);
    void indexImage(const Directory &parent, const QFileInfo &infos);
};

#endif // DIRINDEXER_H
