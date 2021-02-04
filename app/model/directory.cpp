#include "directory.h"

Directory::Directory(QString path, IndexingStrategy strategy):
    QDir(path),
    strategy(strategy)
{}

bool Directory::equal(const Directory& dir) const
{
    return absolutePath() == dir.absolutePath() && strategy == dir.strategy;
}

bool Directory::operator== (const Directory& dir) const
{
    return absolutePath() == dir.absolutePath();
}
