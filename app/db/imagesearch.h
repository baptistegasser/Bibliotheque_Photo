#ifndef IMAGESEARCH_H
#define IMAGESEARCH_H

#include <QString>

/**
 * @brief Represent the different params used to search, filter and order images.
 */
class ImageSearch
{
public:
    /**
     * @brief The valids sort fields
     */
    enum SortBy {
        Name,
        Size,
        Date,
        Rating,
        None
    };

    // The keyword to search
    QString keyword;
    // The values used to filter results
    int minWidth, maxWidth;
    int minHeight, maxHeight;
    int minRating;
    // Apply a sort during search
    SortBy sortOrder;
    bool sortDescendant;

    ImageSearch();
    void resetKeyword();
    void resetFilter();
    void resetOrder();
};

#endif // IMAGESEARCH_H
