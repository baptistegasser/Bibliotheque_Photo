#include "image.h"

Image::Image(int ID, QString name, ImageDir parentDir, QString path):
    ID(ID),
    name(name),
    parentDir(parentDir),
    path(path)
{
}

QString Image::getComment() const
{
    return comment;
}

void Image::setComment(const QString &value)
{
    comment = value;
}

qint64 Image::getSize() const
{
    return size;
}

void Image::setSize(const qint64 &value)
{
    size = value;
}

int Image::getRating() const
{
    return rating;
}

void Image::setRating(int value)
{
    if (value < 0) {
        rating = 0;
    } else if (value > 5) {
        rating = 5;
    } else {
        rating = value;
    }
}

float Image::getWidth() const
{
    return width;
}

void Image::setWidth(float value)
{
    width = value;
}

float Image::getHeight() const
{
    return height;
}

void Image::setHeight(float value)
{
    height = value;
}


// FEELING TAGS
QList<Tag> Image::getFeelingTags() const
{
    return feelingTags;
}

void Image::setFeelingTags(QList<Tag> tags)
{
    feelingTags = tags;
}

bool Image::addFeelingTag(const Tag tag)
{
    if (!feelingTags.contains(tag)) {
        feelingTags.append(tag);
        return true;
    } else {
        return false;
    }
}

bool Image::removeFeelingTag(const Tag tag)
{
    return feelingTags.removeOne(tag);
}


// CATERGORY TAGS
QList<Tag> Image::getCategoryTags() const
{
    return categoryTags;
}

void Image::setCategoryTags(QList<Tag> tags)
{
    categoryTags = tags;
}

bool Image::addCategoryTag(const Tag tag)
{
    if (!categoryTags.contains(tag)) {
        categoryTags.append(tag);
        return true;
    } else {
        return false;
    }
}

bool Image::removeCategoryTag(const Tag tag)
{
    return categoryTags.removeOne(tag);
}


// DESCRIPTIVE TAGS
QList<Tag> Image::getDescriptiveTags() const
{
    return descriptiveTags;
}

void Image::setDescriptiveTags(QList<Tag> tags)
{
    descriptiveTags = tags;
}

bool Image::addDescriptiveTag(const Tag tag)
{
    if (!descriptiveTags.contains(tag)) {
        descriptiveTags.append(tag);
        return true;
    } else {
        return false;
    }
}

bool Image::removeDescriptiveTag(const Tag tag)
{
    return descriptiveTags.removeOne(tag);
}
