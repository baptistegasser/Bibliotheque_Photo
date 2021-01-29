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

    bool create(Tag *tag);
    bool update(Tag *tag);
    bool remove(Tag *tag);
    QList<Tag *> getAll();
    Tag *getById(int id);

    QList<Tag *> getFeelingTags(int imageID);
    QList<Tag *> getFeelingTags(const Image *image);
    QList<Tag *> getDescriptiveTags(int imageID);
    QList<Tag *> getDescriptiveTags(const Image *image);
    QList<Tag *> getCategoryTags(int imageID);
    QList<Tag *> getCategoryTags(const Image *image);

private:
    Tag *fromRecord(QSqlRecord record);
    QList<Tag *> getTagsFromImage(QString table, int imageID);
};

#endif // TAGDAO_H
