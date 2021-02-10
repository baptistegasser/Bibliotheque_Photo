#include "filter.h"

#include "float.h"
#include "limits.h"

Filter::Filter()
{
    reset();
}

void Filter::reset()
{
    minWidth = 0;
    maxWidth = 0;
    minHeight = 0;
    maxHeight = 0;
    minRating = 0;
}
