#ifndef IMAGE_H
#define IMAGE_H

#include "tag.h"
#include "imagedir.h"

#include "QString"
#include "QList"

class Image
{
public:
    const int ID;               // Unique id of the image
    const QString name;         // The image name
    const ImageDir parentDir;   // Directory containing this image
    const QString path;         // Relative path of the image inside the parentDir

    QString comment;            // A comment for the image
    qint64 size;                // The file size in bytes
    int rating;                 // A note between 0 and 5
    float width;
    float height;

    QList<Tag> feelingTags;     // Tags relative to the feeling given by the image
    QList<Tag> categoryTags;    // Tags relative to general/abstract aspect of an image
    QList<Tag> descriptiveTags; // Tags that describe precisly the image content

    Image(int ID, QString name, ImageDir parentDir, QString path);

    QString getComment() const;
    void setComment(const QString &value);

    qint64 getSize() const;
    void setSize(const qint64 &value);

    int getRating() const;
    void setRating(int value);

    float getWidth() const;
    void setWidth(float value);

    float getHeight() const;
    void setHeight(float value);

    QList<Tag> getFeelingTags() const;
    void setFeelingTags(QList<Tag> tags);
    bool addFeelingTag(const Tag tag);
    bool removeFeelingTag(const Tag tag);

    QList<Tag> getCategoryTags() const;
    void setCategoryTags(QList<Tag> tags);
    bool addCategoryTag(const Tag tag);
    bool removeCategoryTag(const Tag tag);

    QList<Tag> getDescriptiveTags() const;
    void setDescriptiveTags(QList<Tag> tags);
    bool addDescriptiveTag(const Tag tag);
    bool removeDescriptiveTag(const Tag tag);
};

#endif // IMAGE_H
