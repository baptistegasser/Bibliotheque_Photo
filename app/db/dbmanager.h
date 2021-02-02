#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "imagedao.h"
#include "imagedirdao.h"
#include "tagdao.h"
#include "directorydao.h"

#include <QSqlDatabase>
#include <QString>

class DBManager
{
private:
    static QString DB_PATH;
    static DBManager *instance;

    QSqlDatabase *m_db;
    TagDAO *tagDao;
    ImageDAO *imageDao;
    ImageDirDAO *imageDirDao;
    DirectoryDAO *directoryDao;

    DBManager();
    ~DBManager();

public:
    static void init();
    static void close();
    static void overrideDBPath(QString newPath);
    static DBManager *getInstance();
    static void assertInit();
    static TagDAO getTagDao();
    static ImageDAO getImageDao();
    static ImageDirDAO getImageDirDao();
    static DirectoryDAO getDirectoryDao();

    class DBException : public std::exception {
    private:
        QString message;

    public:
        DBException(): DBException("Unkown message") {}
        DBException(QString message): std::exception(), message(message) {}
        const char* what() const noexcept override { return message.toUtf8().data(); }
    };
};

#endif // DBMANAGER_H
