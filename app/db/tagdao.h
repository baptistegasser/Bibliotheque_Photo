#ifndef TAGDAO_H
#define TAGDAO_H

#include "dao.h"
#include "model/tag.h"
#include "model/image.h"

#include "QSqlRecord"

class TagDAO : DAO<Tag>
{
public:
    using DAO::DAO;

    bool exist(Tag &tag);
    bool exist(QString value);
    bool save(Tag &tag);
    bool saveAll(Tag tags[]);
    bool saveAll(QList<Tag> tags);
    bool remove(Tag &tag);
    Tag getByValue(QString value);
    QList<Tag> getAll();
    QList<Tag> search(QString key);

    bool saveImageTags(const Image &img);
    bool removeImageTags(const Image &img);
    QList<Tag> getFeelingTags(const Image &img);
    QList<Tag> getDescriptiveTags(const Image &img);
    QList<Tag> getCategoryTags(const Image &img);

private:
    bool create(Tag &tag);
    bool update(Tag &tag);
    Tag fromRecord(QSqlRecord record);

    bool saveImageTags(const Image &img, const QList<Tag> tags, QString table);
    QList<Tag> getImageTags(const Image &img, QString table);
};

#endif // TAGDAO_H
