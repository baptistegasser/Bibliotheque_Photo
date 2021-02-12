#ifndef ALBUMDAO_H
#define ALBUMDAO_H

#include "db/dao.h"

class AlbumDAO : DAO
{
public:
    using DAO::DAO;

    bool exist(QString name);
    QList<QString> getAlbums();
    bool createAlbum(QString name);
    bool removeAlbum(QString name);
};

#endif // ALBUMDAO_H
