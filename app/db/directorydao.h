#ifndef DIRECTORYDAO_H
#define DIRECTORYDAO_H

#include "dao.h"
#include "model/directory.h"
#include <QSqlRecord>

class DirectoryDAO : public DAO<Directory>
{
public:
    using DAO::DAO;

    bool exist(Directory &directory);
    bool save(Directory &directory);
    bool saveAll(Directory directories[]);
    bool saveAll(QList<Directory> directories);
    bool remove(Directory &directory);
    QList<Directory> getAll();

private:
    bool create(Directory &directory);
    bool update(Directory &directory);
};

#endif // DIRECTORYDAO_H
