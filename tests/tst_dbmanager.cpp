#include "tst_dbmanager.h"

#include <QDebug>
#include <QtTest>

QString DBManagerTest::testDBPath = ""; // tmp declaration

void DBManagerTest::initTestCase()
{
    // Assert file was correctly cleaned after previous tests
    // and override the default file path
    testDBPath = QDir(qApp->applicationDirPath()).absoluteFilePath("test.db");
    QVERIFY2(!QFileInfo(testDBPath).exists(), "Test database already exist");
    DBManager::overrideDBPath(testDBPath);
}

// Clean the created database
void DBManagerTest::cleanup()
{
    DBManager::close();
    QFile file(testDBPath);
    if (file.exists()) {
        QVERIFY2(file.remove(), ("Failed to delete db file at " + testDBPath).toUtf8().data());
    }
}

void DBManagerTest::test_init()
{
    QFileInfo file(testDBPath);

    QVERIFY(!file.exists());
    DBManager::init();
    QVERIFY(file.exists());
    DBManager::close();
    QVERIFY2(QFile::remove(testDBPath), ("Failed to delete db file at " + testDBPath).toUtf8().data());
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
    QVERIFY(!QFileInfo(testDBPath).exists());
    DBManager::overrideDBPath(testDBPath);
    DBManager::init();
    QVERIFY(QFileInfo(testDBPath).exists());
    DBManager::close();
    QFile(testDBPath).remove();
}

void DBManagerTest::test_getInstance()
{
    QVERIFY_EXCEPTION_THROWN(DBManager::getInstance(), DBManager::DBException);

    DBManager::init();
    QVERIFY(DBManager::getInstance() != nullptr);
}
