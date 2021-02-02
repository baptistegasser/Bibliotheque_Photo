#ifndef DBMANAGERTEST_H
#define DBMANAGERTEST_H

#include "db/dbmanager.h"
#include <QApplication>
#include <QObject>

class DBManagerTest : public QObject
{
    Q_OBJECT

public:
    DBManagerTest() {
        int _ = 0;
        app = new QApplication(_, {});
    };
    ~DBManagerTest() {
        delete app;
    };

private:
    static QString testDBPath;
    QApplication *app;

private slots:
    void initTestCase();
    void cleanup();

    void test_init();
    void test_close();
    void test_overrideDBPath();
    void test_getInstance();
};

#endif // DBMANAGERTEST_H
