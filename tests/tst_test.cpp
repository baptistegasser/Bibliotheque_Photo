#include <QtTest>

#include <QDebug>

class Test : public QObject
{
    Q_OBJECT

public:
    Test();
    ~Test();

private slots:
    void test_case1();

};

Test::Test()
{

}

Test::~Test()
{

}

void Test::test_case1()
{
    qDebug("Test is run now");
}

QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
