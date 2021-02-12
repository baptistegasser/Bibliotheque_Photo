#ifndef DIRECTORYDAO_H
#define DIRECTORYDAO_H

#include "dao.h"
#include "model/directory.h"
#include <QSqlRecord>

class DirectoryDAO : public DAO
{
public:
    using DAO::DAO;

    bool exist(Directory &directory);
    bool save(Directory &directory);
    bool saveAll(Directory directories[]);
    bool saveAll(QList<Directory> directories);
    bool remove(Directory &directory);
    Directory getByPath(const QString path);
    QList<Directory> getAll();
    QList<Directory> getChildDirs(const Directory &dir);

private:
    bool create(Directory &directory);
    bool update(Directory &directory);
    Directory fromRecord(const QSqlRecord &record);
};

#endif // DIRECTORYDAO_H
