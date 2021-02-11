#include "imagesearch.h"

ImageSearch::ImageSearch()
{
    resetKeyword();
    resetFilter();
    resetOrder();
}

void ImageSearch::resetKeyword()
{
    keyword = QString::Null();
}

void ImageSearch::resetFilter()
{
    minWidth = 0;
    maxWidth = 0;
    minHeight = 0;
    maxHeight = 0;
    minRating = 0;
}

void ImageSearch::resetOrder()
{
    sortOrder = None;
    sortDescendant = true;
}
