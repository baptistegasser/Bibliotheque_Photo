#include "imagedao.h"

#include "QDebug"
#include "QSqlError"
#include "db.h"

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

    bool success = true;
    if (exist(image)) {
        success &= update(image);
    } else {
        success &= create(image);
    }

    success &= DB::getTagDao().saveImageTags(image);

    return success;
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
    query.prepare("INSERT INTO Image (\"Path\", ParentDir, Name, \"Size\", Width, Height, Rating, Comment, Resized, ResWidth, ResHeight, Cropped, CropX, CropY, CropWidth, CropHeight) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    query.addBindValue(image.path);
    query.addBindValue(image.parentDir);
    query.addBindValue(image.name);
    query.addBindValue(image.size);
    query.addBindValue(image.width);
    query.addBindValue(image.height);
    query.addBindValue(image.rating);
    query.addBindValue(image.comment);
    query.addBindValue(image.resized);
    query.addBindValue(image.res_width);
    query.addBindValue(image.res_height);
    query.addBindValue(image.cropped);
    query.addBindValue(image.crop_x);
    query.addBindValue(image.crop_y);
    query.addBindValue(image.crop_width);
    query.addBindValue(image.crop_height);

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
    query.prepare("UPDATE Image SET ParentDir=?, Name=?, \"Size\"=?, Width=?, Height=?, Rating=?, Comment=?, Resized=?, ResWidth=?, ResHeight=?, Cropped=?, CropX=?, CropY=?, CropWidth=?, CropHeight=? WHERE \"Path\"=?;");
    query.addBindValue(image.parentDir);
    query.addBindValue(image.name);
    query.addBindValue(image.size);
    query.addBindValue(image.width);
    query.addBindValue(image.height);
    query.addBindValue(image.rating);
    query.addBindValue(image.comment);
    query.addBindValue(image.resized);
    query.addBindValue(image.res_width);
    query.addBindValue(image.res_height);
    query.addBindValue(image.cropped);
    query.addBindValue(image.crop_x);
    query.addBindValue(image.crop_y);
    query.addBindValue(image.crop_width);
    query.addBindValue(image.crop_height);
    query.addBindValue(image.path);

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

    bool success = query.numRowsAffected() == 1;
    success &= DB::getTagDao().removeImageTags(image);
    return success;
}

QList<Image> ImageDAO::getAll()
{
    return search(QString::Null(), Filter::Empty());
}

QList<Image> ImageDAO::getAll(Filter filter)
{
    return search(QString::Null(), filter);
    QList<Image> result;
    QSqlQuery query = getNewQuery();

    if (!query.exec("SELECT * FROM Image WHERE Width >= ? AND Height <= ? and Rating >= ?;")) {
        qWarning("Failed to get all images");
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

QList<Image> ImageDAO::search(QString keyword)
{
    return search(keyword, Filter::Empty());
}

QList<Image> ImageDAO::search(const QString keyword, const Filter filter)
{
    QString SQL = "SELECT * FROM :TABLES: :SEARCH: :FILTER:;";

    QString _tables = "Image";
    QString _search = "";
    QString _filter = "";

    if (!keyword.isEmpty()) {
        _tables = "Image, ImageCategory c, ImageDescriptive d, ImageFeeling f";
        _search = "WHERE Name LIKE :keyword OR Comment LIKE :keyword OR (\"Path\" = c.ImgPath AND c.TagValue LIKE :keyword) OR (\"Path\" = d.ImgPath AND d.TagValue LIKE :keyword) OR (\"Path\" = f.ImgPath AND f.TagValue LIKE :keyword)";
    }

    if (!filter.isEmpty()) {
        _tables = "Image, ImageCategory c, ImageDescriptive d, ImageFeeling f";
        _filter = "WHERE Width>=? AND Width<=? AND Height>=? AND Height<=? AND Rating>=? ";
        if (filter.containTag.size()) {
            QString _in = "IN (";
            int i = 0;
            for (; i < filter.containTag.size()-1; ++i) {
                _in += ":tag"+QString::number(i)+",";
            }
            _in += ":tag"+QString::number(i+1)+")";
            _filter += "AND ( (\"Path\" = c.ImgPath AND c.TagValue "+_in+") OR (\"Path\" = d.ImgPath AND d.TagValue "+_in+") OR (\"Path\" = f.ImgPath AND f.TagValue "+_in+") ) ";
        }
        if (filter.dontContainTag.size()) {
            QString _in = "NOT IN (";
            int i = 0;
            for (; i < filter.dontContainTag.size()-1; ++i) {
                _in += ":tag"+QString::number(i)+",";
            }
            _in += ":tag"+QString::number(i+1)+")";
            _filter += "AND ( (\"Path\" = c.ImgPath AND c.TagValue "+_in+") OR (\"Path\" = d.ImgPath AND d.TagValue "+_in+") OR (\"Path\" = f.ImgPath AND f.TagValue "+_in+") ) ";
        }
    }

    SQL = SQL.replace(":TABLES:", _tables).replace(":SEARCH:", _search).replace(":FILTER:", _filter);

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);

    if (!keyword.isEmpty()) {
        query.bindValue(":keyword", "%"+keyword+"%");
    }
    if (!filter.isEmpty()) {
        query.addBindValue(filter.minWidth);
        query.addBindValue(filter.maxWidth);
        query.addBindValue(filter.minHeight);
        query.addBindValue(filter.maxHeight);
        query.addBindValue(filter.minRating);
        if (filter.containTag.size()) {
            const QString tag = ":tag";
            for (int i = 0; i < filter.containTag.size(); ++i) {
                query.bindValue(tag+i, filter.containTag[i]);
            }
        }
        if (filter.dontContainTag.size()) {
            const QString tag = ":tag";
            for (int i = 0; i < filter.dontContainTag.size(); ++i) {
                query.bindValue(tag+i, filter.dontContainTag[i]);
            }
        }
    }

    QList<Image> result;
    if (!query.exec()) {
        qWarning() << "Failed to get a list of images" << "Keyword: "+keyword << query.lastQuery();
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result << fromRecord(query.record());
    }

    return result;
}

QList<Image> ImageDAO::getInDir(const Directory &dir)
{
    QList<Image> result;

    QSqlQuery query = getNewQuery();
    query.prepare("SELECT * FROM Image WHERE ParentDir = ?;");
    query.addBindValue(dir.absolutePath());

    if (!query.exec()) {
        qWarning() << "Failed to search images in dir" << dir;
        qCritical() << query.lastError().text();
        return result;
    }

    while (query.next()) {
        result.append(fromRecord(query.record()));
    }

    return result;
}

Image ImageDAO::fromRecord(QSqlRecord record)
{
    Image img;
    img.path = record.value("Path").toString();
    img.parentDir = record.value("ParentDir").toString();
    img.name = record.value("Name").toString();
    img.size = record.value("Size").toInt();
    img.width = record.value("Width").toInt();
    img.height = record.value("Height").toInt();
    img.rating = record.value("Rating").toInt();
    img.comment = record.value("Comment").toString();
    img.resized = record.value("Resized").toBool();
    img.res_width = record.value("ResWidth").toInt();
    img.res_height = record.value("ResHeight").toInt();
    img.cropped = record.value("Cropped").toBool();
    img.crop_x = record.value("CropX").toInt();
    img.crop_y = record.value("CropY").toInt();
    img.crop_width = record.value("CropWidth").toInt();
    img.crop_height = record.value("CropHeight").toInt();

    TagDAO tagDao = DB::getTagDao();
    img.feelingTags = tagDao.getFeelingTags(img);
    img.descriptiveTags = tagDao.getDescriptiveTags(img);
    img.categoryTags = tagDao.getCategoryTags(img);

    return img;
}
