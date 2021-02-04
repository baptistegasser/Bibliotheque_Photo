#ifndef DIRECTORYDAOTEST_H
#define DIRECTORYDAOTEST_H

#include "dbtest.h"
#include "model/directory.h"
#include <QList>
#include <QObject>

class DirectoryDAOTest : public QObject, private DBTest
{
    Q_OBJECT;

public:
    using DBTest::DBTest;

private:
    QList<Directory> directories;

private slots:
    void init();
    void cleanup();

    void test_creation();
    void test_exist();
    void test_update();
    void test_remove();
};

#endif // DIRECTORYDAOTEST_H
