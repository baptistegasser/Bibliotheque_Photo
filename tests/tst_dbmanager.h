#ifndef DBMANAGERTEST_H
#define DBMANAGERTEST_H

#include "dbtest.h"
#include <QObject>

class DBManagerTest : public QObject, private DBTest
{
    Q_OBJECT

private slots:
    void cleanup();

    void test_init();
    void test_close();
    void test_overrideDBPath();
    void test_getInstance();
};

#endif // DBMANAGERTEST_H
