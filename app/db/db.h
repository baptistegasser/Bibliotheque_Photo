#ifndef DB_H
#define DB_H

#include "albumdao.h"
#include "imagedao.h"
#include "tagdao.h"
#include "directorydao.h"

#include <QSqlDatabase>
#include <QString>

class DB
{
private:
    static QString DB_PATH;
    static DB *instance;

    QSqlDatabase *m_db;
    TagDAO *tagDao;
    ImageDAO *imageDao;
    DirectoryDAO *directoryDao;
    AlbumDAO *albumDao;

    DB();
    ~DB();

public:
    static void init();
    static void close();
    static void overrideDBPath(QString newPath);
    static DB *getInstance();
    static void assertInit();
    static TagDAO getTagDao();
    static ImageDAO getImageDao();
    static DirectoryDAO getDirectoryDao();
    static AlbumDAO getAlbumDAO();

    class DBException : public std::exception {
    private:
        QString message;

    public:
        DBException(): DBException("Unkown message") {}
        DBException(QString message): std::exception(), message(message) {}
        const char* what() const noexcept override { return message.toUtf8().data(); }
    };
};

#endif // DB_H
