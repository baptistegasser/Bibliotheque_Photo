#include "directorydao.h"

bool DirectoryDAO::exist(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT 1 FROM Directory WHERE \"Path\" = ?;");
    query.bindValue(0, directory.absolutePath());

    return query.exec() && query.next();
}

bool DirectoryDAO::save(Directory &directory)
{
    if (exist(directory)) {
        return update(directory);
    } else {
        return create(directory);
    }
}

bool DirectoryDAO::saveAll(Directory directories[])
{
    bool status = true;

    int i = 0, l = *(&directories + 1) - directories;
    for (; i < l; ++i) {
        status &= save(directories[i]);
    }

    return status;
}

bool DirectoryDAO::saveAll(QList<Directory> directories)
{
    bool status = true;

    int i = 0, l = directories.size();
    for (; i < l; ++i) {
        status &= save(directories[i]);
    }

    return status;
}

bool DirectoryDAO::create(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("INSERT INTO Directory(\"Path\", Strategy) VALUES(?, ?);");
    query.bindValue(0, directory.absolutePath());
    query.bindValue(1, (int) directory.strategy);

    if (!query.exec()) {
        qWarning() << "Creating directory failed" << directory;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DirectoryDAO::update(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("UPDATE Directory SET Strategy = ? WHERE \"Path\" = ?;");
    query.bindValue(0, (int) directory.strategy);
    query.bindValue(1, directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Updating directory failed" << directory;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DirectoryDAO::remove(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("DELETE FROM Directory WHERE \"Path\" = ?;");
    query.bindValue(0, directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Removing directory failed" << directory;
        qCritical() << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() == 1;
}

QList<Directory> DirectoryDAO::getAll()
{
    QList<Directory> result;
    QSqlQuery query = getNewQuery();

    if (!query.exec("SELECT * FROM Directory;")) {
        qWarning("Failed to get all directories");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        QString path = query.value("Path").toString();
        int strategy = query.value("Strategy").toInt();
        result.append(Directory(path, static_cast<Directory::IndexingStrategy>(strategy)));
    }

    return result;
}
