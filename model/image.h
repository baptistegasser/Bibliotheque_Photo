#ifndef IMAGE_H
#define IMAGE_H

#include "tag.h"
#include "imagedir.h"

#include "QString"
#include "QList"

class Image
{
public:
    Image() = default;

    int ID;             // Unique id of the image
    QString name;       // The image name
    ImageDir parentDir; // Directory containing this image
    QString path;       // Relative path of the image inside the parentDir

    QString comment;    // A comment for the image
    qint64 size;        // The file size in bytes
    int rating;         // A note between 0 and 5
    float width;
    float height;

    QList<Tag *> feelingTags;     // Tags relative to the feeling given by the image
    QList<Tag *> categoryTags;    // Tags relative to general/abstract aspect of an image
    QList<Tag *> descriptiveTags; // Tags that describe precisly the image content
};

#endif // IMAGE_H
