#include "imagedirdao.h"

#include "dbmanager.h"
#include "QDebug"

bool ImageDirDAO::create(ImageDir *imageDir)
{
    QString SQL = "";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, imageDir->path);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to create ImageDir");
        return false;
    }

    QVariant ID = query->lastInsertId();
    if (query->numRowsAffected() == 1 && ID.isValid() && ID.canConvert(QVariant::Int)) {
        imageDir->ID = ID.toInt();
        return true;
    } else {
        return false;
    }
}

bool ImageDirDAO::update(ImageDir *imageDir)
{
    QString SQL = "UPDATE ImageDir SET \"Path\" = ? WHERE ID = ?;";

    QSqlQuery* query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, imageDir->path);
    query->bindValue(1, imageDir->ID);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to update ImageDir with ID = '%d'", imageDir->ID);
        return false;
    }

    return query->numRowsAffected() == 1;
}

bool ImageDirDAO::remove(ImageDir *imageDir)
{
    QString SQL = "DELETE FROM ImageDir WHERE ID = ?;";

    QSqlQuery* query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, imageDir->ID);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to remove ImageDir with ID = '%d'", imageDir->ID);
        return false;
    }

    return query->numRowsAffected() == 1;
}

QList<ImageDir *> ImageDirDAO::getAll()
{
    QString SQL = "SELECT * FROM ImageDir";
    QSqlQuery *query = getNewQuery();

    QList<ImageDir *> result;

    if (!query->exec(SQL) || !query->isValid()) {
        qWarning("Failed to get all ImageDirs");
        return result;
    }

    while (query->next()) {
        result.append(fromRecord(query->record()));
    }

    return result;
}

ImageDir *ImageDirDAO::getById(int id)
{
    QString SQL = "SELECT * FROM ImageDir WHERE ID = ?;";

    QSqlQuery *query = getNewQuery();
    query->prepare(SQL);
    query->bindValue(0, id);

    if (!query->exec() || !query->isValid()) {
        qWarning("Failed to get ImageDir with ID = '%d'", id);
        return NULL;
    }

    if (query->next()) {
        return fromRecord(query->record());
    } else {
        qWarning("No ImageDir found for ID = '%d'", id);
        return NULL;
    }
}

ImageDir *ImageDirDAO::fromRecord(QSqlRecord record)
{
    ImageDir *imageDir = new ImageDir();

    imageDir->ID = record.value("ID").toInt();
    imageDir->path = record.value("Path").toString();

    return imageDir;
}
