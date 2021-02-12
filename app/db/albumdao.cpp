#include "albumdao.h"

bool AlbumDAO::exist(QString name)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT 1 FROM Album WHERE Name = ?;");
    query.addBindValue(name);

    return query.exec() && query.next();
}

QList<QString> AlbumDAO::getAlbums()
{
    QList<QString> result;
    QSqlQuery query = getNewQuery();

    if (!query.exec("SELECT * FROM Album;")) {
        qWarning("Failed to get all albums");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result << query.value("Name").toString();
    }

    return result;
}

bool AlbumDAO::createAlbum(QString name)
{
    QSqlQuery query = getNewQuery();
    query.prepare("INSERT INTO Album (Name) VALUES(?);");
    query.addBindValue(name);

    if (!query.exec()) {
        qWarning() << "Failed to create album" << name;
        qCritical() << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() == 1;
}

bool AlbumDAO::removeAlbum(QString name)
{
    QSqlQuery query = getNewQuery();
    query.prepare("DELETE FROM Album WHERE Name = ?;");
    query.addBindValue(name);

    if (!query.exec()) {
        qWarning() << "Failed to remove album" << name;
        qCritical() << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() == 1;
}
