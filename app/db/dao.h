#ifndef DAO_H
#define DAO_H

#include "QList"
#include "QSqlDatabase"
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
    QSqlQuery *getNewQuery() { return new QSqlQuery(m_db); }
};

#endif // DAO_H
