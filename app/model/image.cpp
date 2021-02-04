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
}

Image::Image(QString path) : Image(QFileInfo(path))
{
}

Image::Image(QFileInfo infos) : Image()
{
    path = infos.absoluteFilePath();

    if (!infos.exists()) {
        qCritical("The given file don't exist");
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
    return QString("{ Path: %1 }").arg(path);
}
