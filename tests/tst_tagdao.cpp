#include "tst_tagdao.h"

#include "db/dbmanager.h"
#include <QDebug>


void TagDAOTest::init()
{
    DBTest::init();
}

void TagDAOTest::cleanup()
{
    DBTest::cleanup();
}

void TagDAOTest::test_save()
{ // Check the creation and update via save()
    Tag tag_1("Moutain");
    Tag tag_2("Dog");
    Tag tag_3("Tree", "#00ff00");

    TagDAO tagDao = DBManager::getTagDao();

    tagDao.save(tag_1);
    tagDao.saveAll({tag_2, tag_3});

    QList<Tag> tags = tagDao.getAll();
    QVERIFY(tag_1 == tags[0]);
    QVERIFY(tag_2 == tags[1]);
    QVERIFY(tag_3 == tags[2]);

    tag_1.color = "#ff0000";
    QVERIFY(!tag_1.equal(tags[0]));
    tag_2.color = "#00ff00";
    QVERIFY(!tag_2.equal(tags[1]));

    tagDao.saveAll({tag_1, tag_2});

    tags = tagDao.getAll();
    QVERIFY(tag_1 == tags[0]);
    QVERIFY(tag_2 == tags[1]);
    QVERIFY(tag_3 == tags[2]);
}

void TagDAOTest::test_remove()
{
    QList<Tag> tags = {
        Tag("Moutain"),
        Tag("Dog"),
        Tag("Tree", "#00ff00")
    };
    TagDAO tagDao = DBManager::getTagDao();

    tagDao.saveAll(tags);

    QVERIFY(tagDao.remove(tags[1]));
    QCOMPARE(tagDao.getAll().size(), 2);
    QVERIFY(tagDao.remove(tags[2]));
    QCOMPARE(tagDao.getAll().size(), 1);
    QCOMPARE(tagDao.getAll()[0], tags[0]);
    QVERIFY(!tagDao.remove(tags[1]));
}

void TagDAOTest::test_search()
{
    QList<Tag> tags = {
        Tag("Moutain"),
        Tag("Dog"),
        Tag("Tree", "#00ff00")
    };
    TagDAO tagDao = DBManager::getTagDao();
    tagDao.saveAll(tags);

    QCOMPARE(tagDao.search("something").size(), 0);
    QCOMPARE(tagDao.search("Moutain").size(), 1);
    QCOMPARE(tagDao.search("o").size(), 2);
}


