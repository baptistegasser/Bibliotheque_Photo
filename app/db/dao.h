#ifndef DAO_H
#define DAO_H

#include "QDebug"
#include "QList"
#include "QSqlDatabase"
#include "QSqlError"
#include "QSqlQuery"
#include "QVariant"

template <typename T>
class DAO
{
public:
    DAO(QSqlDatabase db): m_db(db) {};
    virtual bool create(T *dto) = 0;
    virtual bool update(T *dto) = 0;
    virtual bool remove(T *dto) = 0;
    virtual QList<T *> getAll() = 0;
    virtual T *getById(int id) = 0;

private:
    QSqlDatabase m_db;

protected:
    QSqlQuery getNewQuery() { return QSqlQuery(m_db); }
    // Simple wrapper that execute a prepared query and throw a warning
    // if it fail. The string is a description of the query
    bool execQuery(QSqlQuery *query, QString description) const
    {
        if (query->exec()) {
            return true;
        } else {
            qWarning() << "Failed to " + description << query->lastError().text();
            return false;
        }
    }
};

#endif // DAO_H
