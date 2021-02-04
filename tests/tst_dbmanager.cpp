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
    DB::init();
    QVERIFY(file.exists());
    DB::close();
    QVERIFY2(QFile::remove(path), ("Failed to delete db file at " + path).toUtf8().data());
}

void DBManagerTest::test_close()
{
    DB::init();
    QVERIFY(DB::getInstance() != nullptr);
    DB::close();
    QVERIFY_EXCEPTION_THROWN(DB::getInstance(), DB::DBException);
}

void DBManagerTest::test_overrideDBPath()
{
    QVERIFY(!QFileInfo(path).exists());
    DB::overrideDBPath(path);
    DB::init();
    QVERIFY(QFileInfo(path).exists());
    DB::close();
    QFile(path).remove();
}

void DBManagerTest::test_getInstance()
{
    QVERIFY_EXCEPTION_THROWN(DB::getInstance(), DB::DBException);

    DB::init();
    QVERIFY(DB::getInstance() != nullptr);
}
