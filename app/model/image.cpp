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
    if (!infos.exists()) {
        qCritical("The given file don't exist");
        path = infos.path();
        return;
    }

    path = infos.absoluteFilePath();
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

bool Image::operator== (const Image& img) const
{
    return name == img.name &&
            path == img.path &&
            comment == img.comment &&
            size == img.size &&
            rating == img.rating &&
            width == img.width &&
            height == img.height &&
            feelingTags == img.feelingTags &&
            categoryTags == img.categoryTags &&
            descriptiveTags == img.descriptiveTags;
}

bool Image::operator!= (const Image& img) const
{
    return !(*this == img);
}

Image::operator QString() const
{
    return QString("{ Path: %1 }").arg(path);
}
