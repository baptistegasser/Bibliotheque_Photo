#ifndef IMAGEDIRDAO_H
#define IMAGEDIRDAO_H

#include "dao.h"
#include "model/imagedir.h"

#include "QSqlRecord"

class ImageDirDAO : DAO<ImageDir>
{
public:
    using DAO::DAO;

    bool create(ImageDir *imageDir);
    bool update(ImageDir *imageDir);
    bool remove(ImageDir *imageDir);
    QList<ImageDir *> getAll();
    ImageDir *getById(int id);

private:
    ImageDir *fromRecord(QSqlRecord record);
};

#endif // IMAGEDIRDAO_H
