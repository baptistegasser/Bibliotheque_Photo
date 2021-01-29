#ifndef IMAGEDAO_H
#define IMAGEDAO_H

#include "dao.h"
#include "model/image.h"

#include "QSqlRecord"

class ImageDAO : DAO<Image>
{
public:
    using DAO::DAO;

    bool create(Image *image);
    bool update(Image *image);
    bool remove(Image *image);
    QList<Image *> getAll();
    Image *getById(int id);

private:
    Image *fromRecord(QSqlRecord record);
};

#endif // IMAGEDAO_H
