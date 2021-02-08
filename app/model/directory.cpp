#include "directory.h"

Directory Directory::INVALID = Directory("INVALID", EXCLUDE);

Directory::Directory()
{
    strategy = EXCLUDE;
    this->parentDirPath = QString::Null();
}

Directory::Directory(QString path, IndexingStrategy strategy):
    QDir(path),
    strategy(strategy)
{
    this->parentDirPath = QString::Null();
}

bool Directory::isParentDir()
{
    return this->parentDirPath.isNull() || this->parentDirPath.isEmpty();
}

bool Directory::equal(const Directory& dir) const
{
    return absolutePath() == dir.absolutePath();
}

bool Directory::operator== (const Directory& dir) const
{
    return absolutePath() == dir.absolutePath();
}

Directory::operator QString() const
{
    QString strat;
    switch (strategy) {
    case INCLUDE:
        strat = "INCLUDE";
        break;
    case EXCLUDE:
        strat = "EXCLUDE";
        break;
    default:
        strat = "UNKNOWN";
    };
    return absolutePath() + " " + strat;
}
