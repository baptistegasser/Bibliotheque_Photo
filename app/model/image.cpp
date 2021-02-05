#include "image.h"

#include <QImage>

Image::Image()
{
    path = "";
    name = "";
    size = 0;
    width = 0;
    height = 0;
    rating = 0;
    comment = "";
    resized = false;
    res_width = 0;
    res_height = 0;
    cropped = false;
    crop_x = 0;
    crop_y = 0;
    crop_width = 0;
    crop_height = 0;
}

Image::Image(QString path) : Image(QFileInfo(path))
{
}

Image::Image(QFileInfo infos) : Image()
{
    path = infos.absoluteFilePath();

    if (!infos.exists()) {
        //qCritical("The given file don't exist");
        return;
    }

    name = infos.baseName();
    size = infos.size();

    QImage q_img (infos.absoluteFilePath());
    if (q_img.isNull()) {
        qCritical("The given file is not a valid image");
        return;
    }

    width = q_img.width();
    height = q_img.height();
}

bool Image::equal(const Image& img) const
{
    return path == img.path &&
            name == img.name &&
            size == img.size &&
            width == img.width &&
            height == img.height &&
            rating == img.rating &&
            comment == img.comment &&
            feelingTags == img.feelingTags &&
            descriptiveTags == img.descriptiveTags &&
            categoryTags == img.categoryTags;
}

bool Image::operator== (const Image& img) const
{
    return path == img.path;
}

bool Image::operator!= (const Image& img) const
{
    return !(*this == img);
}

Image::operator QString() const
{
    QString s("{\n\tpath: %path%\n\tname: %name%\n\tsize: %size%, width: %width%, height: %height%, rating: %rating%\n\tcomment: %comment%\n\tfeelingTags: { %feelingTags% }\n\tdescriptiveTags: { %descriptiveTags% }\n\tcategoryTags: { %categoryTags% }\n}");

    s.replace("\t", "    ");
    s.replace("%path%", path);
    s.replace("%name%", name);
    s.replace("%size%", QString::number(size));
    s.replace("%width%", QString::number(width));
    s.replace("%height%", QString::number(height));
    s.replace("%rating%", QString::number(rating));
    s.replace("%comment%", comment);
    s.replace("%feelingTags%", Tag::listToQString(feelingTags));
    s.replace("%descriptiveTags%", Tag::listToQString(descriptiveTags));
    s.replace("%categoryTags%", Tag::listToQString(categoryTags));

    return s;
}
