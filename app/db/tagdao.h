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
    bool save(Tag &tag);
    bool saveAll(Tag tags[]);
    bool saveAll(QList<Tag> tags);
    bool remove(Tag &tag);
    QList<Tag> getAll();
    QList<Tag> search(QString key);

private:
    bool create(Tag &tag);
    bool update(Tag &tag);
    Tag fromRecord(QSqlRecord record);

public:
    QList<Tag *> getFeelingTags(int imageID);
    QList<Tag *> getFeelingTags(const Image *image);
    QList<Tag *> getDescriptiveTags(int imageID);
    QList<Tag *> getDescriptiveTags(const Image *image);
    QList<Tag *> getCategoryTags(int imageID);
    QList<Tag *> getCategoryTags(const Image *image);

};

#endif // TAGDAO_H
