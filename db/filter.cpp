#include "filter.h"

#include "float.h"
#include "limits.h"

Filter::Filter():
    minSize(LLONG_MIN),
    maxSize(LLONG_MAX),
    minWidth(FLT_MIN),
    maxWidth(FLT_MAX),
    minRating(0)
{
}
