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
    query.prepare("INSERT INTO Directory(\"Path\", ParentDirPath, Strategy) VALUES(?, ?, ?);");
    query.addBindValue(directory.absolutePath());
    query.addBindValue(directory.parentDirPath);
    query.addBindValue((int) directory.strategy);

    if (!query.exec()) {
        qWarning() << "Creating directory failed" << directory.operator QString();
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DirectoryDAO::update(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("UPDATE Directory SET ParentDirPath=?, Strategy=? WHERE \"Path\" = ?;");
    query.addBindValue(directory.parentDirPath);
    query.addBindValue((int) directory.strategy);
    query.addBindValue(directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Updating directory failed" << directory.operator QString();
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool DirectoryDAO::remove(Directory &directory)
{
    QSqlQuery query = getNewQuery();
    query.prepare("DELETE FROM Image WHERE ParentDir = :path");
    query.bindValue(":path", directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Removing images from parent dir failed" << query.lastQuery() << directory.operator QString();
        qCritical() << query.lastError().text();
        return false;
    }

    int numRows = query.numRowsAffected();

    query.finish();
    query = getNewQuery();
    query.prepare("DELETE FROM Image WHERE ParentDir IN (SELECT \"Path\" FROM Directory WHERE Directory.\"Path\" = Image.ParentDir AND Directory.ParentDirPath = :path);");
    query.bindValue(":path", directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Removing images from sub dir failed" << query.lastQuery() << directory.operator QString();
        qCritical() << query.lastError().text();
        return false;
    }

    numRows += query.numRowsAffected();

    query.finish();
    query = getNewQuery();
    query.prepare("DELETE FROM Directory WHERE \"Path\" =:path OR ParentDirPath = :path;");
    query.bindValue(":path", directory.absolutePath());

    if (!query.exec()) {
        qWarning() << "Removing directory failed" << query.lastQuery() << directory.operator QString();
        qCritical() << query.lastError().text();
        return false;
    }

    return (numRows + query.numRowsAffected()) >= 1;
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
        result << fromRecord(query.record());
    }

    return result;
}

Directory DirectoryDAO::fromRecord(const QSqlRecord &record)
{
    Directory dir;
    dir.setPath(record.value("Path").toString());
    dir.parentDirPath = record.value("ParentDirPath").toString();
    dir.strategy = static_cast<Directory::IndexingStrategy>(record.value("Strategy").toInt());
    return dir;
}

QList<Directory> DirectoryDAO::getChildDirs(const Directory &dir)
{
    QList<Directory> childs;
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT * FROM Directory WHERE ParentDirPath = ?;");
    query.addBindValue(dir.absolutePath());

    if (!query.exec()) {
        qWarning("Failed to get all child directory");
        qCritical() << query.lastError().text();
        return childs;
    }

    while (query.next()) {
        childs << fromRecord(query.record());
    }

    return childs;
}

Directory DirectoryDAO::getByPath(const QString path)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT * FROM Directory WHERE \"Path\" = ?;");
    query.addBindValue(path);

    if (!query.exec()) {
        qWarning("Failed to get all child directory");
        qCritical() << query.lastError().text();
        return Directory::INVALID;
    }


    if (query.next()) {
        return fromRecord(query.record());
    } else {
        return Directory::INVALID;
    }
}
