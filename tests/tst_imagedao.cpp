#include "tst_imagedao.h"

#include "db/imagedao.h"

void ImageDAOTest::COMPARE_IMAGES(QList<Image> actual, QList<Image> expected)
{
    for (const Image &img : actual) {
        int i = expected.indexOf(img);
        QVERIFY2(i != -1, "Image in l1 not present in l2");

        if (!img.equal(expected.at(i))) {
            qDebug().noquote() << "\nActual:" << img << "\n" << "\nExpected:" << expected.at(i);
            QVERIFY2(img.equal(expected.at(i)), "Image in l1 not equal to image in l2");
        }
    }
}

void ImageDAOTest::init()
{
    DBTest::init();
    images = {
        Image(),
        Image(),
        Image(),
        Image(),
        Image(),
    };

    for (int i = 0; i < 5; ++i) {
        images[i].path = "/fake/path/0" + QString::number(i);
    }

    images[0].feelingTags = { Tag("first feel") };
    images[0].descriptiveTags = { Tag("first descr") };
    images[0].categoryTags = { Tag("first cat") };
}

void ImageDAOTest::cleanup()
{
    DBTest::cleanup();
}

void ImageDAOTest::test_exist()
{
    ImageDAO imageDao = DB::getImageDao();
    for (int i (0); i < images.size(); ++i) {
        QVERIFY(!imageDao.exist(images[i]));
        QVERIFY(imageDao.save(images[i]));
        QVERIFY(imageDao.exist(images[i]));
    }
}

void ImageDAOTest::test_creation()
{
    ImageDAO imageDao = DB::getImageDao();

    QVERIFY(imageDao.save(images[0]));
    QCOMPARE(imageDao.getAll().size(), 1);

    QVERIFY(imageDao.saveAll({ images[1], images[2] }));
    QCOMPARE(imageDao.getAll().size(), 3);

    QVERIFY(imageDao.saveAll(images.mid(3)));
    QCOMPARE(imageDao.getAll().size(), 5);

    COMPARE_IMAGES(imageDao.getAll(), images);
}

void ImageDAOTest::test_update()
{
    ImageDAO imageDao = DB::getImageDao();
    imageDao.save(images[0]);
    COMPARE_IMAGES(imageDao.getAll(), {images[0]});

    // Insert datas
    QVERIFY(imageDao.saveAll(images));
    COMPARE_IMAGES(imageDao.getAll(), images);

    // Change a dir strategy and save
    images[0].name = "Custom name";
    QVERIFY(imageDao.save(images[0]));
    COMPARE_IMAGES(imageDao.getAll(), images);

    // A valid update always success even when not changing anything
    images[4].name = images[4].name;
    QVERIFY(imageDao.exist(images[4]));
    QVERIFY(imageDao.save(images[4]));
}

void ImageDAOTest::test_remove()
{
    ImageDAO imageDao = DB::getImageDao();
    // Insert datas
    QVERIFY(imageDao.saveAll(images));
    COMPARE_IMAGES(imageDao.getAll(), images);

    QVERIFY(imageDao.remove(images[0]));
    QCOMPARE(imageDao.getAll().size(), images.size()-1);
    COMPARE_IMAGES(imageDao.getAll(), images.mid(1));

    // Deleting something already deleted
    QVERIFY(imageDao.remove(images[0]) == false);
}
