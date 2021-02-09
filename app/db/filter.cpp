#include "filter.h"

#include "float.h"
#include "limits.h"

Filter* Filter::EMPTY;

Filter::Filter()
{
    minWidth = FLT_MIN;
    minHeight = FLT_MIN;
    maxWidth = FLT_MAX;
    maxHeight = FLT_MAX;
    minRating = 0;
}

Filter Filter::Empty()
{
    if (EMPTY == nullptr) {
        EMPTY = new Filter();
        EMPTY->m_empty = true;
    }

    return *EMPTY;
}

bool Filter::isEmpty() const
{
    return this->m_empty;
}
