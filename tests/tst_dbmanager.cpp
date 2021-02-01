#include "tst_dbmanager.h"

#include <QApplication>
#include <QDebug>
#include <QtTest>

QString DBManagerTest::testDBPath = ""; // tmp declaration

void DBManagerTest::initTestCase()
{
    // This code took 20min of my life, it doesn't deserve a var name.
    // Also, it init the qApp used by the db.
    int _ = 0; QApplication a(_, {});

    // Assert file was correctly cleaned after previous tests
    // and override the default file path
    testDBPath = QDir(qApp->applicationDirPath()).absoluteFilePath("test.db");
    QVERIFY2(!QFileInfo(testDBPath).exists(), "Test database already exist");
    DBManager::overrideDBPath(testDBPath);
}

// Create a fresh database for the test
void DBManagerTest::init()
{
    qDebug("INIT");
    DBManager::init();
    qDebug("END_INIT");
}

// Clean the created database
void DBManagerTest::cleanup()
{
    qDebug("CLEANUP");
    DBManager::close();
    QVERIFY2(QFile::remove(testDBPath), ("Failed to delete db file at " + testDBPath).toUtf8().data());
    qDebug("END_CLEANUP");
}

void DBManagerTest::test_init()
{

}

void DBManagerTest::test_close()
{

}

void DBManagerTest::test_overrideDBPath()
{

}

void DBManagerTest::test_getInstance()
{
    // Act like no database nor connection exist
    cleanup();
    QVERIFY_EXCEPTION_THROWN(DBManager::getInstance(), DBManager::DBException);

    DBManager::init();
    QVERIFY(DBManager::getInstance() != nullptr);
}
