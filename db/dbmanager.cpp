#include "dbmanager.h"

#include "QDebug"
#include "QSqlError"
#include "QSqlQuery"
#include "QSqlRecord"
#include "QSqlResult"

DBManager::DBManager()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(DB_PATH);

    qDebug() << "Opening database connection at " << DB_PATH;

    if (!m_db.open()) {
        m_lastErrorMsg = "Failed to open database, cause: \n" + m_db.lastError().text();
        throw DBException();
    }

    qInfo("Connection successfull");
}

DBManager::~DBManager()
{
    qDebug("Closing database connection");
    if (m_db.isOpen()) {
        m_db.close();
    }
}

// Get the last error message
QString DBManager::lastErrorMsg() const
{
    return m_lastErrorMsg;
}

Tag* DBManager::getTag(const int tagID)
{
    QSqlQuery* query = selectFromTableByID("Tag", tagID);
    QSqlRecord record = query->record();

    if (!query->isValid() || record.isEmpty()) {
        return NULL;
    }

    QString value = record.value("Value").toString();
    QString color = record.value("Color").toString();

    return new Tag(tagID, value, color);
}

Image* DBManager::getImage(const int imageID)
{
    QSqlQuery* query = selectFromTableByID("Image", imageID);
    QSqlRecord record = query->record();

    if (!query->isValid() || record.isEmpty()) {
        qWarning() << "Failed to find an image with ID=" << imageID;
        return NULL;
    }

    ImageDir parentDir = *getImageDir(record.value("DirID").toInt());
    QString name = record.value("Name").toString();
    QString path = record.value("Path").toString();

    Image* image = new Image(imageID, name, parentDir, path);

    image->setComment(record.value("Comment").toString());
    image->setSize(record.value("Size").toInt());
    image->setRating(record.value("Rating").toInt());
    image->setWidth(record.value("Width").toFloat());
    image->setHeight(record.value("Height").toFloat());

    image->setFeelingTags(getFeelingTags(imageID));
    image->setCategoryTags(getCategoryTag(imageID));
    image->setDescriptiveTags(getDescriptiveTags(imageID));

    return image;
}

ImageDir* DBManager::getImageDir(const int imageDirID)
{
    QSqlQuery* query = selectFromTableByID("ImageDir", imageDirID);
    QSqlRecord record = query->record();

    if (!query->isValid() || record.isEmpty()) {
        return NULL;
    }

    QString path = record.value("Path").toString();

    return new ImageDir(imageDirID, path);
}

QSqlQuery* DBManager::selectFromTableByID(QString table, int ID)
{
    QString SQL = "SELECT FROM %TABLE% WHERE ID = :id LIMIT 1;";

    QSqlQuery* query = new QSqlQuery(m_db);
    bool success = query->prepare(SQL.replace("%TABLE%", table));

    if (!success) {
        m_lastErrorMsg = "Failed to prepare select query for table: " + table;
        throw DBManager::DBException();
    }

    query->bindValue(":id", ID);
    if (!query->exec()) {
        m_lastErrorMsg = QString("Failed to run select on table '%1' width ID='%2', cause: \n%3").arg(table, QString::number(ID), query->lastError().text());
        throw DBException();
    }

    query->next(); // Set the pointer to the first (and only) record
    return query;
}

QList<Tag> DBManager::getFeelingTags (int imageID)
{
    return getTags("ImageFeeling", imageID);
}

QList<Tag> DBManager::getCategoryTag (int imageID)
{
    return getTags("ImageCategory", imageID);
}

QList<Tag> DBManager::getDescriptiveTags(int imageID)
{
    return getTags("ImageDescription", imageID);
}

QList<Tag> DBManager::getTags(QString tagTable, int imageID)
{
    QString SQL = "SELECT TagID FROM %TABLE% WHERE ImageID = :id";

    QSqlQuery* query = new QSqlQuery(m_db);
    bool success = query->prepare(SQL.replace("%TABLE%", tagTable));

    if (!success) {
        m_lastErrorMsg = "Failed to prepare tag selecttion query for table: " + tagTable;
        throw DBManager::DBException();
    }

    query->bindValue(":id", imageID);
    if (!query->exec()) {
        m_lastErrorMsg = QString("Failed to run select on table '%1' width ImageID='%2', cause: \n%3").arg(tagTable, QString::number(imageID), query->lastError().text());
        throw DBException();
    }

    QList<Tag> tags;

    QSqlRecord record;
    while (query->next()) {
        const int tagID = record.value("TagID").toInt();
        Tag* tag = getTag(tagID);
        if (tag != NULL) {
            tags.append(*tag);
        }
    }

    return tags;
}

