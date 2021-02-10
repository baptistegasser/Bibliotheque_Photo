#include "filter.h"

#include "float.h"
#include "limits.h"

Filter* Filter::EMPTY;

Filter::Filter()
{
    reset();
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

void Filter::reset()
{
    minWidth = 0;
    maxWidth = 0;
    minHeight = 0;
    maxHeight = 0;
    minRating = 0;
}
