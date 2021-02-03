#include "tst_taglist.h"

#include "model/taglist.h"

void TagListTest::init()
{
    m_tags = {
        Tag("first"),
        Tag("second"),
        Tag("third")
    };
}


void TagListTest::test_list()
{
    TagList list;

    // Add two tags
    list.add(m_tags[0]);
    list.add(m_tags[1]);
    QCOMPARE(list.size(), 2);
    QCOMPARE(list.getAdded().size(), 2);
    QCOMPARE(list.getRemoved().size(), 0);

    // Remove one of the freshly added tag
    list.remove(m_tags[0]);
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.getAdded().size(), 1);
    QCOMPARE(list.getRemoved().size(), 0);

    // Commit changes
    list.commit();

    // Remove a commited tag and add new one
    list.remove(m_tags[1]);
    list.add(m_tags[2]);
    QCOMPARE(list.size(), 1);
    QCOMPARE(list.getAdded().size(), 1);
    QCOMPARE(list.getRemoved().size(), 1);
}

void TagListTest::test_contains()
{
    TagList list;
    list.add(m_tags[0]);

    QVERIFY(list.contains(m_tags[0]));
    QVERIFY(!list.contains(m_tags[1]));
}
