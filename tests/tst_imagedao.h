#ifndef IMAGEDAOTEST_H
#define IMAGEDAOTEST_H

#include "dbtest.h"
#include <QObject>

class ImageDAOTest : public QObject, private DBTest
{
    Q_OBJECT;

public:
    using DBTest::DBTest;

private slots:
    void init() { DBTest::init(); };
    void cleanup() { DBTest::cleanup(); };


};

#endif // IMAGEDAOTEST_H
