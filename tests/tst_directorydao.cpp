#include "tst_directorydao.h"

#include "db/directorydao.h"

void DirectoryDAOTest::init()
{
    DBTest::init();
    directories = {
        Directory("/path/to/fake/dir/01", Directory::IndexingStrategy::INCLUDE),
        Directory("/path/to/fake/dir/02", Directory::IndexingStrategy::INCLUDE),
        Directory("/path/to/fake/dir/03", Directory::IndexingStrategy::INCLUDE),
        Directory("/path/to/fake/dir/04", Directory::IndexingStrategy::EXCLUDE),
        Directory("/path/to/fake/dir/05", Directory::IndexingStrategy::EXCLUDE),
        Directory("/path/to/fake/dir/06", Directory::IndexingStrategy::EXCLUDE)
    };
}

void DirectoryDAOTest::cleanup()
{
    DBTest::cleanup();
}

void DirectoryDAOTest::test_creation()
{
    DirectoryDAO dirDao = DBManager::getDirectoryDao();
    QVERIFY(dirDao.getAll().isEmpty());

    // Insert a single dir
    QVERIFY(dirDao.save(directories[0]));
    QCOMPARE(dirDao.getAll().size(), 1);
    // Insert an array of dir
    QVERIFY(dirDao.saveAll({ directories[1], directories[2] }));
    QCOMPARE(dirDao.getAll().size(), 3);
    // Insert a QList of dir
    QVERIFY(dirDao.saveAll(directories.mid(3)));
    QCOMPARE(dirDao.getAll().size(), directories.size());
    // Assert that all inserted value can be retrieved with same values
    QList<Directory> createdDir = dirDao.getAll();
    QCOMPARE(createdDir, directories);
}

void DirectoryDAOTest::test_exist()
{
    DirectoryDAO dirDao = DBManager::getDirectoryDao();
    QVERIFY(dirDao.getAll().isEmpty());

    QVERIFY(dirDao.save(directories[0]));
    QVERIFY(dirDao.exist(directories[0]));
}

void DirectoryDAOTest::test_update()
{
    DirectoryDAO dirDao = DBManager::getDirectoryDao();
    // Insert datas
    QVERIFY(dirDao.saveAll(directories));
    QCOMPARE(dirDao.getAll(), directories);

    // Change a dir strategy and save
    directories[0].strategy = Directory::IndexingStrategy::EXCLUDE;
    QVERIFY(dirDao.save(directories[0]));
    QCOMPARE(dirDao.getAll(), directories);

    // A valid update always success even when not changing anything
    directories[5].strategy = directories[5].strategy;
    QVERIFY(dirDao.exist(directories[5]));
    QVERIFY(dirDao.save(directories[5]));
}

void DirectoryDAOTest::test_remove()
{
    DirectoryDAO dirDao = DBManager::getDirectoryDao();
    // Insert datas
    QVERIFY(dirDao.saveAll(directories));
    QCOMPARE(dirDao.getAll(), directories);

    QVERIFY(dirDao.remove(directories[0]));
    QCOMPARE(dirDao.getAll().size(), directories.size()-1);
    QCOMPARE(dirDao.getAll(), directories.mid(1));

    // Deleting something already deleted
    QVERIFY(dirDao.remove(directories[0]) == false);
}
