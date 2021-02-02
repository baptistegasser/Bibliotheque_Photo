#include "tst_dbmanager.h"

#include <QDebug>
#include <QtTest>


void DBManagerTest::cleanup()
{
    DBTest::cleanup();
}

void DBManagerTest::test_init()
{
    QFileInfo file(path);

    QVERIFY(!file.exists());
    DBManager::init();
    QVERIFY(file.exists());
    DBManager::close();
    QVERIFY2(QFile::remove(path), ("Failed to delete db file at " + path).toUtf8().data());
}

void DBManagerTest::test_close()
{
    DBManager::init();
    QVERIFY(DBManager::getInstance() != nullptr);
    DBManager::close();
    QVERIFY_EXCEPTION_THROWN(DBManager::getInstance(), DBManager::DBException);
}

void DBManagerTest::test_overrideDBPath()
{
    QVERIFY(!QFileInfo(path).exists());
    DBManager::overrideDBPath(path);
    DBManager::init();
    QVERIFY(QFileInfo(path).exists());
    DBManager::close();
    QFile(path).remove();
}

void DBManagerTest::test_getInstance()
{
    QVERIFY_EXCEPTION_THROWN(DBManager::getInstance(), DBManager::DBException);

    DBManager::init();
    QVERIFY(DBManager::getInstance() != nullptr);
}
