#ifndef FILTER_H
#define FILTER_H

#include "model/tag.h"

#include "QList"
#include "QString"

class Filter
{
public:
    QList<QString> containTag;      // List of tag that should be on the image
    QList<QString> dontContainTag;  // List of tag value not to be found on the image

    qint64 minSize, maxSize;
    float minWidth, maxWidth;
    int minRating;

    Filter();
};

#endif // FILTER_H
