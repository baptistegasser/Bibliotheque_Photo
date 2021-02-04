#ifndef IMAGEDAO_H
#define IMAGEDAO_H

#include "dao.h"
#include "model/image.h"
#include "filter.h"
#include "QSqlRecord"

class ImageDAO : public DAO<Image>
{
public:
    using DAO::DAO;

    bool exist(Image &image);
    bool save(Image &image);
    bool saveAll(Image images[]);
    bool saveAll(QList<Image> images);
    bool remove(Image &image);
    QList<Image> getAll();
    QList<Image> search(Filter filter);

private:
    bool create(Image &image);
    bool update(Image &image);
    Image fromRecord(QSqlRecord record);
};

#endif // IMAGEDAO_H
