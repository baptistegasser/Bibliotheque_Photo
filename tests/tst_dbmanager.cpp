#include <QtTest>

#include "db/dbmanager.h"
#include <QApplication>
#include <QDebug>

class DBManagerTest : public QObject
{
    Q_OBJECT

public:
    DBManagerTest() {};
    ~DBManagerTest() {};

private:
    static QString testDBPath;

private slots:
    void test_case1();
    void initTestCase();
    void cleanupTestCase();
};

QString DBManagerTest::testDBPath = ""; // tmp declaration

void DBManagerTest::initTestCase()
{
    int _ = 0; QApplication a(_, {}); // This code took 20min of my life, it doesn't deserve a var name

    testDBPath = QDir(qApp->applicationDirPath()).absoluteFilePath("test.db");
    QVERIFY2(!QFileInfo(testDBPath).exists(), "Test database already exist");

    DBManager::overrideDBPath(testDBPath);
    DBManager::init();

    QCOMPARE(DBManager::getInstance()->getTagDao().getAll().size(), 0);
    QCOMPARE(DBManager::getInstance()->getImageDao().getAll().size(), 0);
    QCOMPARE(DBManager::getInstance()->getImageDirDao().getAll().size(), 0);
}

void DBManagerTest::test_case1()
{

}

void DBManagerTest::cleanupTestCase()
{
    QVERIFY2(QFile::remove(testDBPath), ("Failed to delete db file at " + testDBPath).toUtf8().data());
}

QTEST_APPLESS_MAIN(DBManagerTest)

#include "tst_dbmanager.moc"
