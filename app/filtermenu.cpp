#include "filtermenu.h"

FilterMenu::FilterMenu(ImageSearch *search, QWidget *parent) :
    QMenu(parent),
    search(search)
{
    setupUi(this);
    connect(this, &QMenu::aboutToHide, this, &FilterMenu::updateFilter);

    stars = QList<QPushButton *>();
    for (int i = 1; i <= 5; ++i) {
        QPushButton *btn = new QPushButton(QIcon(":/image/star_empty"), "");
        connect(btn, &QPushButton::clicked, this, [=]() { this->setCurrentRating(i); });
        _star_area->addWidget(btn);
        stars.append(btn);
    }

    updateDisplay();
}

/**
 * Update the request with filter value
 * @brief FilterMenu::updateFilter
 */
void FilterMenu::updateFilter()
{
    search->minWidth = _min_width_box->value();
    search->maxWidth = _max_width_box->value();
    search->minHeight = _min_height_box->value();
    search->maxHeight = _max_height_box->value();

    emit filterUpdated();
}

/**
 * Update the visual of the star filter
 * @brief FilterMenu::setCurrentRating
 * @param rating
 */
void FilterMenu::setCurrentRating(int rating)
{
    for (int i = 0; i < 5; ++i) {
        if (rating >= i+1) {
            stars[i]->setIcon(QIcon(":/image/star_full"));
        } else {
            stars[i]->setIcon(QIcon(":/image/star_empty"));
        }
    }

    search->minRating = rating;
}

/**
 * Update the visual
 * @brief FilterMenu::updateDisplay
 */
void FilterMenu::updateDisplay()
{
    _min_width_box->setValue(search->minWidth);
    _max_width_box->setValue(search->maxWidth);
    _min_height_box->setValue(search->minHeight);
    _max_height_box->setValue(search->maxHeight);
    setCurrentRating(search->minRating);
}

/**
 * Reset the filter
 * @brief FilterMenu::resetFilter
 */
void FilterMenu::resetFilter()
{
    search->resetFilter();
    updateDisplay();
}
