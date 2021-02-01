#include "dbmanager.h"

#include <QApplication>
#include <QDir>
#include <QSqlError>

// Define static instance
DBManager *DBManager::instance = nullptr;
// Set DB_PATH later
QString DBManager::DB_PATH = QString::Null();

DBManager::DBManager()
{
    // Assert path to DB is set
    if (DB_PATH.isNull()) {
        DB_PATH = QDir(qApp->applicationDirPath()).absoluteFilePath("biblio.db");
    }

    // Assert DB file exist
    if (!QFileInfo::exists(DB_PATH)) {
        // Attempt to copy base DB from resources
        if (!QFile::copy(":/db/init.db", DB_PATH)) {
            throw DBException("Failed to init database by copying template file");
        }
    }

    // Open connection to DB
    m_db = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    m_db->setDatabaseName(DB_PATH);
    if (!m_db->open()) {
        throw DBException("Failed to open database, cause: \n" + m_db->lastError().text());
    }

    // Instanciate Data Access Objects
    tagDao = new TagDAO(m_db);
    imageDao = new ImageDAO(m_db);
    imageDirDao = new ImageDirDAO(m_db);
}

DBManager::~DBManager()
{
    QString name = m_db->connectionName();
    delete m_db;
    delete tagDao;
    QSqlDatabase::removeDatabase(name);
}

// Init the singleton instance, must be explicitly called
void DBManager::init()
{
    if (instance) {
        throw DBException("DB manager already initialized");
    }

    instance = new DBManager();
}

void DBManager::close()
{
    delete instance;
    instance = nullptr;
}

void DBManager::overrideDBPath(QString newPath)
{
    if (instance) {
        qWarning("The DBManager instance is initialized, change will apply after closing it.");
    }

    DB_PATH = newPath;
}

DBManager *DBManager::getInstance()
{
    if (!instance) {
        throw DBException("DB manager was not initialized, please call init() first");
    }

    return instance;
}

TagDAO DBManager::getTagDao() const
{
    return *tagDao;
}

ImageDAO DBManager::getImageDao() const
{
    return *imageDao;
}

ImageDirDAO DBManager::getImageDirDao() const
{
    return *imageDirDao;
}
