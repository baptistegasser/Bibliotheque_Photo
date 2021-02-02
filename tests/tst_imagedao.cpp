#include "tst_imagedao.h"

#include "db/imagedao.h"

void ImageDAOTest::init()
{
    DBTest::init();
    images = {
        Image("/fake/path/01"),
        Image("/fake/path/02"),
        Image("/fake/path/03"),
        Image("/fake/path/04"),
        Image("/fake/path/05"),
    };
}

void ImageDAOTest::cleanup()
{
    DBTest::cleanup();
}

void ImageDAOTest::test_exist()
{
    ImageDAO imageDao = DBManager::getImageDao();
    for (int i (0); i < images.size(); ++i) {
        QVERIFY(!imageDao.exist(images[i]));
        QVERIFY(imageDao.save(images[i]));
        QVERIFY(imageDao.exist(images[i]));
    }
}

void ImageDAOTest::test_creation()
{
    ImageDAO imageDao = DBManager::getImageDao();

    QVERIFY(imageDao.save(images[0]));
    QCOMPARE(imageDao.getAll().size(), 1);

    QVERIFY(imageDao.saveAll({ images[1], images[2] }));
    QCOMPARE(imageDao.getAll().size(), 3);

    QVERIFY(imageDao.saveAll(images.mid(3)));
    QCOMPARE(imageDao.getAll().size(), 5);

    QCOMPARE(imageDao.getAll(), images);
}

void ImageDAOTest::test_update()
{
    ImageDAO imageDao = DBManager::getImageDao();
    // Insert datas
    QVERIFY(imageDao.saveAll(images));
    QCOMPARE(imageDao.getAll(), images);

    // Change a dir strategy and save
    images[0].name = "Custom name";
    QVERIFY(imageDao.save(images[0]));
    QCOMPARE(imageDao.getAll(), images);

    // A valid update always success even when not changing anything
    images[4].name = images[4].name;
    QVERIFY(imageDao.exist(images[4]));
    QVERIFY(imageDao.save(images[4]));
}

void ImageDAOTest::test_remove()
{
    ImageDAO imageDao = DBManager::getImageDao();
    // Insert datas
    QVERIFY(imageDao.saveAll(images));
    QCOMPARE(imageDao.getAll(), images);

    QVERIFY(imageDao.remove(images[0]));
    QCOMPARE(imageDao.getAll().size(), images.size()-1);
    QCOMPARE(imageDao.getAll(), images.mid(1));

    // Deleting something already deleted
    QVERIFY(imageDao.remove(images[0]) == false);
}
