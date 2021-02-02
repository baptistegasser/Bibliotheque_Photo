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

    QString comment;    // A comment for the image
    qint64 size;        // The file size in bytes
    int rating;         // A note between 0 and 5
    float width;
    float height;

    QList<Tag *> feelingTags;     // Tags relative to the feeling given by the image
    QList<Tag *> categoryTags;    // Tags relative to general/abstract aspect of an image
    QList<Tag *> descriptiveTags; // Tags that describe precisly the image content

    Image(QString path);
    Image(QFileInfo infos);

    bool operator== (const Image& img) const;
    bool operator!= (const Image& img) const;
};

#endif // IMAGE_H
