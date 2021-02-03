#ifndef TST_TAGDAO_H
#define TST_TAGDAO_H

#include "dbtest.h"
#include <QObject>

class TagDAOTest : public QObject, private DBTest
{
    Q_OBJECT;

private slots:
    void cleanup();

    void test_1();
    void test_2();
};

#endif // TST_TAGDAO_H
