#ifndef DBMANAGERTEST_H
#define DBMANAGERTEST_H

#include "db/dbmanager.h"
#include <QObject>

class DBManagerTest : public QObject
{
    Q_OBJECT

public:
    DBManagerTest() {};
    ~DBManagerTest() {};

private:
    static QString testDBPath;

private slots:
    void initTestCase();
    void init();
    void cleanup();

    void test_init();
    void test_close();
    void test_overrideDBPath();
    void test_getInstance();
};

#endif // DBMANAGERTEST_H
