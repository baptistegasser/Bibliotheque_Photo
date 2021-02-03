#include <QtTest>

#include "dbtest.h"
#include "tst_taglist.h"
#include "tst_tagdao.h"
#include "tst_dbmanager.h"
#include "tst_imagedao.h"
#include "tst_directorydao.h"

int main(int argc, char *argv[])
{
    int status = 0;

    // Copyright to https://alexhuszagh.github.io/2016/using-qttest-effectively
    // for the base lambda, edited to delete the object
    auto RUN_TEST = [&status, argc, argv](QObject* test) {
        status |= QTest::qExec(test, argc, argv);
        delete test;
    };

    RUN_TEST(new TagListTest());
    RUN_TEST(new DBManagerTest());
    RUN_TEST(new TagDAOTest());
    RUN_TEST(new DirectoryDAOTest());
    RUN_TEST(new ImageDAOTest());

    return status;
}
