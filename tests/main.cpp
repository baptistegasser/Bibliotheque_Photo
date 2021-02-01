#include <QtTest>

#include "tst_tagdao.h"
#include "tst_dbmanager.h"

int main(int argc, char *argv[])
{
    int status = 0;

    // Copyright to https://alexhuszagh.github.io/2016/using-qttest-effectively
    // for the base lambda, edited to delete the object
    auto RUN_TEST = [&status, argc, argv](QObject* test) {
        status |= QTest::qExec(test, argc, argv);
        delete test;
    };

    RUN_TEST(new TagDAOTest());
    RUN_TEST(new DBManagerTest());

    return status;
}
