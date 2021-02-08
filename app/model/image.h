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
    QString parentDir;  // Absolute path to the image dir
    QString name;       // The image name
    qint64 size;        // The file size in bytes
    float width;
    float height;

    int rating;         // A note between 0 and 5
    QString comment;    // A comment for the image

    QList<Tag> feelingTags;     // Tags relative to the feeling given by the image
    QList<Tag> categoryTags;    // Tags relative to general/abstract aspect of an image
    QList<Tag> descriptiveTags; // Tags that describe precisly the image content

    bool resized;     // Is this image resized
    float res_width;  // The resize width
    float res_height; // The resize height

    bool cropped;       // Is this image cropped ?
    float crop_x;       // The X position of the top left corner of the rectangle
    float crop_y;       // The Y position of the top left corner of the rectangle
    float crop_width;   // The crop' rectangle width
    float crop_height;  // The crop' rectangle height

    QVector<int> main_color;  // Vector of RGB main color of the image

    Image();
    Image(const Image &img);
    QVector<int> get_mean_rgb();

    bool equal(const Image& img) const;
    Image operator= (const Image &img) const;
    bool operator== (const Image& img) const;
    bool operator!= (const Image& img) const;
    operator QString() const;

private:
    int get_max(QVector<int> vec);
};

#endif // IMAGE_H
