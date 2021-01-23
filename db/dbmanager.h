#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "filter.h"
#include "model/image.h"

#include <exception>
#include "QApplication"
#include "QDir"
#include "QList"
#include "QSqlDatabase"
#include "QSqlQuery"
#include "QString"

class DBManager
{
private:
     static const QString DB_PATH;
     // The database connection
     QSqlDatabase m_db;

     // Last message set on error
     QString m_lastErrorMsg = "";

     // Prepare and run a query to retrieve a single row with a unique ID
     // from a specified table, return the runned query
     QSqlQuery* selectFromTableByID(QString table, int ID);

     // Methods to get info linked to a specific images
     QList<Tag> getFeelingTags(int imageID);
     QList<Tag> getCategoryTag(int imageID);
     QList<Tag> getDescriptiveTags(int imageID);
     QList<Tag> getTags(QString tagTable, int imageID);


public:
    DBManager();
    ~DBManager();

    // Error handling
    bool error() const;
    QString lastErrorMsg() const;

    // Methods to get individuals elements
    Tag* getTag(const int tagID);
    Image* getImage(const int imageID);
    ImageDir* getImageDir(const int imageDirID);

    // Methods to search images
    QList<Image> searchImage(QString keywords) const;
    QList<Image> searchImage(QString keywords, Filter filter) const;

    // An mock exception used to specify that the excpetion is related to a DB operation
    class DBException : public std::exception {};
};

#endif // DBMANAGER_H
