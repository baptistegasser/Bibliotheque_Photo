#include "imagedao.h"

#include "dbmanager.h"
#include "QDebug"
#include "QSqlError"
/*
bool ImageDAO::create(Image *image)
{
    // Check datas before insert
    if (image->rating < 0) {
        qWarning("Image rating should be >= 0, rounding rating to 0");
        image->rating = 0;
    } else if (image->rating > 5) {
        qWarning("Image rating should be <= 5, rounding rating to 5");
        image->rating = 5;
    }

    QString SQL = "INSERT INTO Image(DirID, Name, \"Path\", \"Size\", Width, Height, Comment, Rating) VALUES(?, ?, ?, ?, ?, ?, ?, ?);";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, image->parentDir.ID);
    query.bindValue(1, image->name);
    query.bindValue(2, image->path);
    query.bindValue(3, image->size);
    query.bindValue(4, image->width);
    query.bindValue(5, image->height);
    query.bindValue(6, image->comment);
    query.bindValue(7, image->rating);

    if (!execQuery(&query, "Create Image")) {
        return false;
    }

    QVariant ID = query.lastInsertId();
    if (query.numRowsAffected() == 1 && ID.isValid() && ID.canConvert(QVariant::Int)) {
        image->ID = ID.toInt();
        return true;
    } else {
        return false;
    }
}

bool ImageDAO::update(Image *image)
{
    QString SQL = "UPDATE Image SET DirID = ?, Name = ?, \"Path\" = ?, \"Size\" = ?, Width = ?, Height = ?, Comment = ?, Rating = ? WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, image->parentDir.ID);
    query.bindValue(1, image->name);
    query.bindValue(2, image->path);
    query.bindValue(3, image->size);
    query.bindValue(4, image->width);
    query.bindValue(5, image->height);
    query.bindValue(6, image->comment);
    query.bindValue(7, image->rating);
    query.bindValue(8, image->ID);

    if (!execQuery(&query, QString("Update Image with ID = '%d'").arg(image->ID))) {
        return false;
    }

    return query.numRowsAffected() == 1;
}

bool ImageDAO::remove(Image *image)
{
    QString SQL = "DELETE FROM Image WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, image->ID);

    if (!execQuery(&query, QString("Remove Image with ID = '%d'").arg(image->ID))) {
        return false;
    }

    return query.numRowsAffected() == 1;
}

QList<Image *> ImageDAO::getAll()
{
    QString SQL = "SELECT * FROM Image;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);

    QList<Image *> result;

    if (!execQuery(&query, "Get all Images")) {
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

Image *ImageDAO::getById(int id)
{
    QString SQL = "SELECT * FROM Image WHERE ID = ?;";

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);
    query.bindValue(0, id);

    if (!execQuery(&query, QString("Get Image with ID = '%d'").arg(id))) {
        return NULL;
    }

    if (query.next()) {
        return fromRecord(query.record());
    } else {
        qWarning("No Image found for ID = '%d'", id);
        return NULL;
    }
}

Image *ImageDAO::fromRecord(QSqlRecord record)
{
    Image* image = new Image();

    image->ID = record.value("ID").toInt();
    image->name = record.value("Name").toString();
    image->parentDir = *DBManager::getInstance()->getImageDirDao().getById(record.value("DirID").toInt());
    image->path = record.value("Path").toString();

    image->comment = record.value("Comment").toString();
    image->size    = record.value("Size").toInt();
    image->rating  = record.value("Rating").toInt();
    image->width   = record.value("Width").toFloat();
    image->height  = record.value("Height").toFloat();

    TagDAO tagDAO = DBManager::getInstance()->getTagDao();
    image->feelingTags = tagDAO.getFeelingTags(image);
    image->descriptiveTags = tagDAO.getDescriptiveTags(image);
    image->categoryTags = tagDAO.getCategoryTags(image);

    return image;
}
*/
