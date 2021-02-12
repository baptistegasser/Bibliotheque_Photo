#ifndef DAO_H
#define DAO_H

#include "QDebug"
#include "QList"
#include "QSqlDatabase"
#include "QSqlError"
#include "QSqlQuery"
#include "QVariant"

class DAO
{
public:
    virtual ~DAO() {};
    DAO(QSqlDatabase *db): m_db(db) {};

private:
    QSqlDatabase *m_db;

protected:
    QSqlQuery getNewQuery() { return QSqlQuery(*m_db); }
};

#endif // DAO_H
