#include "tagdao.h"

#include "dbmanager.h"
#include "QDebug"
#include "QSqlError"

bool TagDAO::exist(Tag &tag)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT 1 FROM Tag WHERE Value = ?;");
    query.bindValue(0, tag.value);

    return query.exec() && query.next();
}

bool TagDAO::create(Tag &tag)
{
    QSqlQuery query = getNewQuery();
    query.prepare("INSERT INTO Tag(Value, Color) VALUES(?, ?);");
    query.bindValue(0, tag.value);
    query.bindValue(1, tag.color);

    if (!query.exec() || query.numRowsAffected() != 1) {
        qWarning() << "Creating tag failed" << tag;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool TagDAO::update(Tag &tag)
{
    QSqlQuery query = getNewQuery();
    query.prepare("UPDATE Tag SET Color = ? WHERE Value = ?;");
    query.bindValue(0, tag.color);
    query.bindValue(1, tag.value);

    if (!query.exec() || query.numRowsAffected() != 1) {
        qWarning() << "Updating tag failed" << tag;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool TagDAO::save(Tag &tag)
{
    if (exist(tag)) {
        return update(tag);
    } else {
        return create(tag);
    }
}

bool TagDAO::saveAll(Tag tags[])
{
    bool status = true;

    int i = 0, l = *(&tags + 1) - tags;
    for (; i < l; ++i) {
        status &= save(tags[i]);
    }

    return status;
}

bool TagDAO::saveAll(QList<Tag> tags)
{
    bool status = true;

    int i = 0, l = tags.size();
    for (; i < l; ++i) {
        status &= save(tags[i]);
    }

    return status;
}

bool TagDAO::remove(Tag &tag)
{
    QSqlQuery query = getNewQuery();
    query.prepare("DELETE FROM Tag WHERE Value = ?;");
    query.bindValue(0, tag.value);

    if (!query.exec()) {
        qWarning() << "Removing tag failed" << tag;
        qCritical() << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() == 1;
}

QList<Tag> TagDAO::getAll()
{
    QList<Tag> result;
    QSqlQuery query = getNewQuery();

    if (!query.exec("SELECT * FROM Tag;")) {
        qWarning("Failed to get all tags");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

QList<Tag> TagDAO::search(QString key)
{
    QList<Tag> result;
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT * FROM Tag WHERE Value = :key OR Value LIKE :search;");
    query.bindValue(":key", key);
    query.bindValue(":search", "%" + key + "%");

    if (!query.exec()) {
        qWarning("Failed to search tags");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

Tag TagDAO::fromRecord(QSqlRecord record)
{
    Tag tag = Tag();
    tag.value = record.value("Value").toString();
    tag.color = record.value("Color").toString();
    return tag;
}


////////////////////////////////////////////////////

/*
bool TagDAO::create(Tag *tag)
{
    QString SQL = "INSERT INTO Tag(Value, Color) VALUES(?, ?);";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, tag->value);
    query.bindValue(1, tag->color);

    if (!execQuery(&query, "Create Tag")) {
        return false;
    }

    QVariant ID = query.lastInsertId();
    if (query.numRowsAffected() == 1 && ID.isValid() && ID.canConvert(QVariant::Int)) {
        tag->ID = ID.toInt();
        return true;
    } else {
        return false;
    }
}

bool TagDAO::update(Tag *tag)
{
    QString SQL = "UPDATE Tag SET Value = ?, Color = ? WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, tag->value);
    query.bindValue(1, tag->color);
    query.bindValue(2, tag->ID);

    if (!execQuery(&query, QString("Update Tag with ID = '%d'").arg(tag->ID))) {
        return false;
    }

    return query.numRowsAffected() == 1;
}

bool TagDAO::remove(Tag *tag)
{
    QString SQL = "DELETE FROM Tag WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, tag->ID);

    if (!execQuery(&query, QString("Remove Tag with ID = '%d").arg(tag->ID))) {
        return false;
    }

    return query.numRowsAffected() == 1;
}

QList<Tag *> TagDAO::getAll()
{
    QString SQL = "SELECT * FROM Tag;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);

    QList<Tag *> result;

    if (!execQuery(&query, "Get all Tags")) {
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

Tag *TagDAO::getById(int id)
{
    QString SQL = "SELECT * FROM Tag WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, id);

    if (!execQuery(&query, QString("Get Tag with ID = '%d'").arg(id))) {
        return NULL;
    }

    if (query.next()) {
        return fromRecord(query.record());
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

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, imageID);

    QList<Tag *> result;

    QString action = QString("Get tags for image %d from table %s").arg(imageID).arg(table);
    if (!execQuery(&query, action)) {
        return result;
    }

    while(query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}
*/
