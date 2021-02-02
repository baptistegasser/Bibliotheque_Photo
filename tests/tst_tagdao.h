#ifndef TST_TAGDAO_H
#define TST_TAGDAO_H

#include "dbtest.h"
#include <QObject>

class TagDAOTest : public QObject, private DBTest
{
    Q_OBJECT;

protected:
    using DBTest::DBTest;

private slots:
    void init();
    void cleanup();

    void test_save();
    void test_remove();
    void test_search();
};

#endif // TST_TAGDAO_H
