#include "imagedao.h"

#include "QDebug"
#include "QSqlError"

bool ImageDAO::exist(Image &image)
{
    QSqlQuery query = getNewQuery();
    query.prepare("SELECT 1 FROM Image WHERE \"Path\" = ?;");
    query.bindValue(0, image.path);

    return query.exec() && query.next();
}

bool ImageDAO::save(Image &image)
{
    if (image.rating < 0) {
        image.rating = 0;
        qWarning("Image rating should be between 0 and 5, rounding to 0");
    } else if (image.rating > 5) {
        image.rating = 5;
        qWarning("Image rating should be between 0 and 5, rounding to 5");
    }

    if (exist(image)) {
        return update(image);
    } else {
        return create(image);
    }
}

bool ImageDAO::saveAll(Image images[])
{
    bool status = true;

    int i = 0, l = *(&images + 1) - images;
    for (; i < l; ++i) {
        status &= save(images[i]);
    }

    return status;
}

bool ImageDAO::saveAll(QList<Image> images)
{
    bool status = true;

    int i = 0, l = images.size();
    for (; i < l; ++i) {
        status &= save(images[i]);
    }

    return status;
}

bool ImageDAO::create(Image &image)
{
    QSqlQuery query = getNewQuery();
    query.prepare("INSERT INTO Image(\"Path\", Name, \"Size\", Width, Height, Rating, Comment) VALUES(?, ?, ?, ?, ?, ?, ?);");
    query.bindValue(0, image.path);
    query.bindValue(1, image.name);
    query.bindValue(2, image.size);
    query.bindValue(3, image.width);
    query.bindValue(4, image.height);
    query.bindValue(5, image.rating);
    query.bindValue(6, image.comment);

    if (!query.exec()) {
        qWarning() << "Creating image failed" << image;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool ImageDAO::update(Image &image)
{
    QSqlQuery query = getNewQuery();
    query.prepare("UPDATE Image SET Name = ?, \"Size\" = ?, Width = ?, Height = ?, Rating = ?, Comment = ? WHERE \"Path\" = ?;");
    query.bindValue(0, image.name);
    query.bindValue(1, image.size);
    query.bindValue(2, image.width);
    query.bindValue(3, image.height);
    query.bindValue(4, image.rating);
    query.bindValue(5, image.comment);
    query.bindValue(6, image.path);

    if (!query.exec()) {
        qWarning() << "Updating image failed" << image;
        qCritical() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool ImageDAO::remove(Image &image)
{
    QSqlQuery query = getNewQuery();
    query.prepare("DELETE FROM Image WHERE \"Path\" = ?;");
    query.bindValue(0, image.path);

    if (!query.exec()) {
        qWarning() << "Removing image failed" << image;
        qCritical() << query.lastError().text();
        return false;
    }

    return query.numRowsAffected() == 1;
}

QList<Image> ImageDAO::getAll()
{
    QList<Image> result;
    QSqlQuery query = getNewQuery();

    if (!query.exec("SELECT * FROM Image;")) {
        qWarning("Failed to get all images");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

QList<Image> ImageDAO::search(Filter filter)
{
    return QList<Image>();
}

Image ImageDAO::fromRecord(QSqlRecord record)
{
    Image img;
    img.path = record.value("Path").toString();
    img.name = record.value("Name").toString();
    img.size = record.value("Size").toInt();
    img.width = record.value("Width").toInt();
    img.height = record.value("Height").toInt();
    img.rating = record.value("Rating").toInt();
    img.comment = record.value("Comment").toString();

    return img;
}
