#ifndef IMAGE_H
#define IMAGE_H

#include "tag.h"

#include <QFileInfo>
#include "QList"
#include "QString"

class Image
{
public:
    QString path;       // Absolute path to the image
    QString name;       // The image name
    qint64 size;        // The file size in bytes
    float width;
    float height;

    int rating;         // A note between 0 and 5
    QString comment;    // A comment for the image

    QList<Tag *> feelingTags;     // Tags relative to the feeling given by the image
    QList<Tag *> categoryTags;    // Tags relative to general/abstract aspect of an image
    QList<Tag *> descriptiveTags; // Tags that describe precisly the image content

    Image();
    Image(QString path);
    Image(QFileInfo infos);

    bool operator== (const Image& img) const;
    bool operator!= (const Image& img) const;
    operator QString() const;
};

#endif // IMAGE_H
