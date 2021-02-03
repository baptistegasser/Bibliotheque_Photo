#ifndef TAGLISTTEST_H
#define TAGLISTTEST_H

#include "model/tag.h"
#include "dbtest.h"
#include <QObject>
#include <QList>

class TagListTest: public QObject, private DBTest
{
    Q_OBJECT;

protected:
    using DBTest::DBTest;

private:
    QList<Tag> m_tags;

private slots:
    void init();

    void test_contains();
    void test_list();
};

#endif // TAGLISTTEST_H
