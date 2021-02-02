#include "tst_tagdao.h"

#include "db/dbmanager.h"
#include <QDebug>

void TagDAOTest::test_1()
{
    qDebug("first test");
}

void TagDAOTest::test_2()
{
    qDebug("second test");
}

void TagDAOTest::cleanup()
{
    DBManager::close();
    QFile file(path);
    if (file.exists()) {
        QVERIFY2(file.remove(), ("Failed to delete db file at " + path).toUtf8().data());
    }
}
