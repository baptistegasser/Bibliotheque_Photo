#ifndef DBTEST_H
#define DBTEST_H

#include "db/dbmanager.h"
#include <QApplication>
#include <QDir>
#include <QTest>

class DBTest
{
protected:
    DBTest()
    {
        int _ = 0;
        app = new QApplication(_, {});
        path = QDir(qApp->applicationDirPath()).absoluteFilePath("test.db");
        QVERIFY2(!QFileInfo(path).exists(), "Test database already exist");
        DBManager::overrideDBPath(path);
    };

    ~DBTest()
    {
        delete app;
        DBManager::close();
        QFile f(path);
        if (f.exists()) f.remove();
    };

private:
    QApplication *app;
protected:
    QString path;
};

#endif // DBTEST_H
