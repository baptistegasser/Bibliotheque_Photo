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

Tag TagDAO::getByValue(QString value)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT * FROM Tag WHERE Value = ?;");
    query.bindValue(0, value);

    if (!query.exec()) {
        qWarning() << "Getting tag failed" << value;
        qCritical() << query.lastError().text();
        return Tag::INVALID;
    }

    if (query.next()) {
        return fromRecord(query.record());
    } else {
        return Tag::INVALID;
    }
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

/*
 * Methods for tags linked to an image
 */
bool TagDAO::saveImageTags(const Image &img)
{
    bool success = true;
    success &= saveImageTags(img, img.feelingTags, "ImageFeeling");
    success &= saveImageTags(img, img.descriptiveTags, "ImageDescriptive");
    success &= saveImageTags(img, img.categoryTags, "ImageCategory");
    return success;
}

bool TagDAO::saveImageTags(const Image &img, const QList<Tag> tags, QString table)
{
    const QList<Tag> current = getImageTags(img, table);
    saveAll(tags);

    QList<Tag> toInsert;
    QList<Tag> toRemove;

    for (const Tag &t : tags) {
        if (!current.contains(t)) {
            toInsert << t;
        }
    }
    for (const Tag &t : current) {
        if (!tags.contains(t)) {
            toRemove << t;
        }
    }

    bool success = true;

    for (const Tag &t : toInsert) {
        QSqlQuery query = getNewQuery();
        query.prepare(QString("INSERT INTO %1 (ImgPath, TagValue) VALUES(?, ?);").arg(table));
        query.addBindValue(img.path);
        query.addBindValue(t.value);

        if (!query.exec()) {
            qWarning() << "Inserting image tags failed" << img << table;
            qCritical() << query.lastError().text();
            success = false;
        }
    }

    for (const Tag &t : toRemove) {
        QSqlQuery query = getNewQuery();
        query.prepare(QString("INSERT INTO %1 (ImgPath, TagValue) VALUES(?, ?);").arg(table));
        query.addBindValue(img.path);
        query.addBindValue(t.value);

        if (!query.exec()) {
            qWarning() << "Inserting image tags failed" << img << table;
            qCritical() << query.lastError().text();
            success = false;
        }
    }

    return success;
}

bool TagDAO::removeImageTags(const Image &img)
{
    QList<QString> tables = {
        "ImageFeeling",
        "ImageDescriptive",
        "ImageCategory"
    };

    bool success = true;
    for (const QString &t : tables) {
        QSqlQuery query = getNewQuery();
        query.prepare(QString("DELETE FROM %1 WHERE ImgPath = ?").arg(t));
        query.addBindValue(img.path);

        if (!query.exec()) {
            qWarning() << "Removing tags from image failed" << img << t;
            qCritical() << query.lastError().text();
            success &= false;
        }
    }

    return success;
}

QList<Tag> TagDAO::getFeelingTags(const Image &img)
{
    return getImageTags(img, "ImageFeeling");
}

QList<Tag> TagDAO::getDescriptiveTags(const Image &img)
{
    return getImageTags(img, "ImageDescriptive");
}

QList<Tag> TagDAO::getCategoryTags(const Image &img)
{
    return getImageTags(img, "ImageCategory");
}

QList<Tag> TagDAO::getImageTags(const Image &img, QString table)
{
    QList<Tag> result;

    QSqlQuery query = getNewQuery();
    query.prepare(QString("SELECT TagValue FROM %1 WHERE ImgPath = ?;").arg(table));
    query.addBindValue(img.path);

    if (!query.exec()) {
        qWarning() << "Failed to get image tags from " + table;
        qCritical() << query.lastError().text();
        return result;
    }

    QList<QString> values;
    while (query.next()) {
        values << query.value("TagValue").toString();
    }

    for (const QString &v : values) {
        result << getByValue(v);
    }

    return result;
}
