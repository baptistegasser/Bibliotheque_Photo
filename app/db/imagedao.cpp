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
    query.prepare("INSERT INTO Image (\"Path\", ParentDir, Album, Name, \"Size\", Width, Height, Rating, Comment, Resized, ResWidth, ResHeight, Cropped, CropX, CropY, CropWidth, CropHeight, MainColor, Date) VALUES(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");

    query.addBindValue(image.path);
    query.addBindValue(image.parentDir);
    query.addBindValue(image.album);
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
    QString mainColorStr = QString("%1;%2;%3")
            .arg(image.main_color[0])
            .arg(image.main_color[1])
            .arg(image.main_color[2]);
    query.addBindValue(mainColorStr);
    query.addBindValue(image.date.toString("yyyy-MM-dd hh:mm:ss"));

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
    query.prepare("UPDATE Image SET ParentDir=?, Album, Name=?, \"Size\"=?, Width=?, Height=?, Rating=?, Comment=?, Resized=?, ResWidth=?, ResHeight=?, Cropped=?, CropX=?, CropY=?, CropWidth=?, CropHeight=?, MainColor=?, Date=? WHERE \"Path\"=?;");
    query.addBindValue(image.parentDir);
    query.addBindValue(image.album);
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
    QString mainColorStr = QString("%1;%2;%3")
            .arg(image.main_color[0])
            .arg(image.main_color[1])
            .arg(image.main_color[2]);
    query.addBindValue(mainColorStr);
    query.addBindValue(image.date.toString("yyyy-MM-dd hh:mm:ss"));

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
    return search(ImageSearch());
}

QList<Image> ImageDAO::search(const ImageSearch &search)
{
    QString SQL = "SELECT * FROM Image Where :SEARCH: :FILTER: :SORT:;";

    QString _search = "True";
    QString _filter = "";
    QString _sort = "";

    if (!search.keyword.isEmpty()) {
        _search = /* sometime I wonder wtf I'm doing */
        "(Name LIKE :keyword OR Comment LIKE :keyword OR \"Path\" IN ("
        "  SELECT ImgPath FROM ImageCategory WHERE TagValue = :tagkeyword"
        "    UNION"
        "  SELECT ImgPath FROM ImageDescriptive WHERE TagValue = :tagkeyword"
        "    UNION"
        "  SELECT ImgPath FROM ImageFeeling WHERE TagValue = :tagkeyword"
        "))";
    }

    if (search.minWidth != 0)  _filter += " AND Width >=  :minWidth";
    if (search.maxWidth != 0)  _filter += " AND Width <=  :maxWidth";
    if (search.minHeight != 0) _filter += " AND Height >= :minHeight";
    if (search.maxHeight != 0) _filter += " AND Height <= :maxHeight";
    if (search.minRating != 0) _filter += " AND Rating >= :minRating";

    if (search.sortOrder != ImageSearch::None) {
        switch (search.sortOrder) {
        case ImageSearch::Name:
            _sort = "ORDER BY LOWER(Name) ";
            break;
        case ImageSearch::Size:
            _sort = "ORDER BY Size ";
            break;
        case ImageSearch::Date:
            _sort = "ORDER BY Date ";
            break;
        case ImageSearch::Rating:
            _sort = "ORDER BY Rating ";
            break;
        }
        _sort += search.sortDescendant ? "ASC" : "DESC";
    }

    SQL = SQL.replace(":SEARCH:", _search).replace(":FILTER:", _filter).replace(":SORT:", _sort);

    QSqlQuery query = getNewQuery();
    query.prepare(SQL);

    if (!search.keyword.isEmpty()) {
        query.bindValue(":keyword", "%"+search.keyword+"%");
        query.bindValue(":tagkeyword", search.keyword);
    }

    if (search.minWidth != 0)  query.bindValue(":minWidth", search.minWidth);
    if (search.maxWidth != 0)  query.bindValue(":maxWidth", search.maxWidth);
    if (search.minHeight != 0) query.bindValue(":minHeight", search.minHeight);
    if (search.maxHeight != 0) query.bindValue(":maxHeight", search.maxHeight);
    if (search.minRating != 0) query.bindValue(":minRating", search.minRating);

    QList<Image> result;
    if (!query.exec()) {
        qWarning() << "Failed to get a list of images" << "Keyword: "+search.keyword << query.lastQuery();
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
    img.album = record.value("Album").toString();
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

    QString mainColorStr = record.value("MainColor").toString();
    QStringList rgb = mainColorStr.split(";");
    for (int i = 0; i < 3; ++i) {
        img.main_color[i] = rgb[i].toInt();
    }

    img.date = QDateTime::fromString(record.value("Date").toString(), "yyyy-MM-dd hh:mm:ss");

    TagDAO tagDao = DB::getTagDao();
    img.feelingTags = tagDao.getFeelingTags(img);
    img.descriptiveTags = tagDao.getDescriptiveTags(img);
    img.categoryTags = tagDao.getCategoryTags(img);

    return img;
}
