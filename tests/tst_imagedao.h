#ifndef IMAGEDAOTEST_H
#define IMAGEDAOTEST_H

#include "dbtest.h"
#include "model/image.h"
#include <QList>
#include <QObject>

class ImageDAOTest : public QObject, private DBTest
{
    Q_OBJECT;

public:
    using DBTest::DBTest;

private:
    QList<Image> images;
    void COMPARE_IMAGES(QList<Image> l1, QList<Image> l2);

private slots:
    void init();
    void cleanup();

    void test_exist();
    void test_creation();
    void test_update();
    void test_remove();
};

#endif // IMAGEDAOTEST_H
