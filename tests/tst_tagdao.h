#ifndef TST_TAGDAO_H
#define TST_TAGDAO_H

#include <QObject>

class TagDAOTest : public QObject
{
    Q_OBJECT;

public:
    TagDAOTest() = default;

private slots:
    void init();
    void test_1();
    void test_2();
    void cleanup();
};

#endif // TST_TAGDAO_H
