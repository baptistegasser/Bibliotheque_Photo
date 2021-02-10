#ifndef FILTER_H
#define FILTER_H

#include "model/tag.h"

#include "QList"
#include "QString"

class Filter
{   
private:
    static Filter *EMPTY;
    bool m_empty = true;

public:
    QList<QString> containTag;      // List of tag that should be on the image
    QList<QString> dontContainTag;  // List of tag value not to be found on the image

    int minWidth, maxWidth;
    int minHeight, maxHeight;
    int minRating;

    Filter();
    static Filter Empty();
    bool isEmpty() const;
    void reset();
};

#endif // FILTER_H
