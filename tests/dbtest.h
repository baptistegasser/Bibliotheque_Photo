#ifndef DBTEST_H
#define DBTEST_H

#include "db/db.h"
#include <QApplication>
#include <QDir>
#include <QTest>

class DBTest
{
public:
    bool deleteDBOnCleanup = true;
    void setDeleteDBOnCleanup(bool d) {
        deleteDBOnCleanup = d;
    }

private:
    QApplication *app;

protected:
    DBTest()
    {
        int _ = 0;
        app = new QApplication(_, {});
        path = QDir(qApp->applicationDirPath()).absoluteFilePath("test.db");
        QVERIFY2(!QFileInfo(path).exists(), "Test database already exist");
        DB::overrideDBPath(path);
    };

    QString path;
    void init()
    {
        DB::init();
    }
    void cleanup()
    {
        DB::close();
        QFile file(path);
        if (file.exists() && deleteDBOnCleanup) {
            QVERIFY2(file.remove(), ("Failed to delete db file at " + path).toUtf8().data());
        }
    }
};

#endif // DBTEST_H
