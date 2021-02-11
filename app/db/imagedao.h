#ifndef IMAGEDAO_H
#define IMAGEDAO_H

#include "dao.h"
#include "model/image.h"
#include "model/directory.h"
#include "filter.h"
#include "QSqlRecord"

class ImageDAO : public DAO<Image>
{
public:
    using DAO::DAO;

    enum SortBy {
        Name,
        Size,
        Date,
        Rating,
        None
    };

    bool exist(Image &image);
    bool save(Image &image);
    bool saveAll(Image images[]);
    bool saveAll(QList<Image> images);
    bool remove(Image &image);
    QList<Image> getAll();
    QList<Image> getAll(Filter filter);
    QList<Image> search(QString keyword);
    QList<Image> search(QString keyword, Filter filter);
    QList<Image> search(QString keyword, Filter filter, SortBy sort, bool ascendant);
    QList<Image> getInDir(const Directory &dir);

private:
    bool create(Image &image);
    bool update(Image &image);
    Image fromRecord(QSqlRecord record);
    void bindFilterToQuery(const QSqlQuery &query, Filter filter);
};

#endif // IMAGEDAO_H
