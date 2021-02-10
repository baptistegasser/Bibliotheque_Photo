#ifndef FILTER_H
#define FILTER_H

#include "model/tag.h"

#include "QList"
#include "QString"

class Filter
{
public:
    int minWidth, maxWidth;
    int minHeight, maxHeight;
    int minRating;

    Filter();
    void reset();
};

#endif // FILTER_H
