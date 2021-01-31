#include "tagdao.h"

#include "dbmanager.h"
#include "QDebug"

bool TagDAO::create(Tag *tag)
{
    QString SQL = "INSERT INTO Tag(Value, Color) VALUES(?, ?);";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, tag->value);
    query->bindValue(1, tag->color);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to create Tag");
        return false;
    }

    QVariant ID = query->lastInsertId();
    if (query->numRowsAffected() == 1 && ID.isValid() && ID.canConvert(QVariant::Int)) {
        tag->ID = ID.toInt();
        return true;
    } else {
        return false;
    }
}

bool TagDAO::update(Tag *tag)
{
    QString SQL = "UPDATE Tag SET Value = ?, Color = ? WHERE ID = ?;";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, tag->value);
    query->bindValue(1, tag->color);
    query->bindValue(2, tag->ID);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to update Tag with ID = '%d'", tag->ID);
        return false;
    }

    return query->numRowsAffected() == 1;
}

bool TagDAO::remove(Tag *tag)
{
    QString SQL = "DELETE FROM Tag WHERE ID = ?;";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, tag->ID);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to remove Tag with ID = '%d'", tag->ID);
        return false;
    }

    return query->numRowsAffected() == 1;
}

QList<Tag *> TagDAO::getAll()
{
    QString SQL = "SELECT * FROM Tag;";
    QSqlQuery *query = getNewQuery();

    QList<Tag *> result;

    if (!query->exec(SQL) || !query->isValid()) {
        qWarning("Failed to get all Tags");
        return result;
    }

    while (query->next()) {
        result.append(fromRecord(query->record()));
    }

    return result;
}

Tag *TagDAO::getById(int id)
{
    QString SQL = "SELECT * FROM Tag WHERE ID = ?;";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, id);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to get Tag with ID = '%d'", id);
        return NULL;
    }

    if (query->next()) {
        return fromRecord(query->record());
    } else {
        qWarning("No Tag found for ID = '%d'", id);
        return NULL;
    }
}

Tag *TagDAO::fromRecord(QSqlRecord record)
{
    Tag *tag = new Tag();

    tag->ID = record.value("ID").toInt();
    tag->value = record.value("Value").toString();
    tag->color = record.value("Color").toString();

    return tag;
}

QList<Tag *> TagDAO::getFeelingTags(const Image *image)
{
    return getFeelingTags(image->ID);
}

QList<Tag *> TagDAO::getFeelingTags(int imageID)
{
    return getTagsFromImage("ImageFeeling", imageID);
}

QList<Tag *> TagDAO::getDescriptiveTags(const Image *image)
{
    return getDescriptiveTags(image->ID);
}

QList<Tag *> TagDAO::getDescriptiveTags(int imageID)
{
    return getTagsFromImage("ImageDescription", imageID);
}

QList<Tag *> TagDAO::getCategoryTags(const Image *image)
{
    return getCategoryTags(image->ID);
}

QList<Tag *> TagDAO::getCategoryTags(int imageID)
{
    return getTagsFromImage("ImageCategory", imageID);
}

// Retrieve tags from an image from a specific linking table: descriptive, feelings...
QList<Tag *> TagDAO::getTagsFromImage(QString table, int imageID)
{
    QString SQL = "SELECT ID, Value, Color FROM Tag, %TABLE% WHERE Tag.ID = %TABLE%.TagID AND %TABLE%.ImageID = ?;";
    SQL.replace("%TABLE%", table);

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, imageID);

    QList<Tag *> result;

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to get tags for image %d from table %s", imageID, table.toUtf8().data());
        return result;
    }

    while(query->next()) {
        result.append(fromRecord(query->record()));
    }

    return result;
}
