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

    if (!query.exec()) {
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

    if (!query.exec()) {
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
