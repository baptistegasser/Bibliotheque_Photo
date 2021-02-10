#include "filtermenu.h"

FilterMenu::FilterMenu(Filter *filter, QWidget *parent) :
    QMenu(parent),
    filter(filter)
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

void FilterMenu::updateFilter()
{
    filter->minWidth = _min_width_box->value();
    filter->maxWidth = _max_width_box->value();
    filter->minHeight = _min_height_box->value();
    filter->maxHeight = _max_height_box->value();

    emit filterUpdated();
}

void FilterMenu::setCurrentRating(int rating)
{
    for (int i = 0; i < 5; ++i) {
        if (rating >= i+1) {
            stars[i]->setIcon(QIcon(":/image/star_full"));
        } else {
            stars[i]->setIcon(QIcon(":/image/star_empty"));
        }
    }

    filter->minRating = rating;
}

void FilterMenu::updateDisplay()
{
    _min_width_box->setValue(filter->minWidth);
    _max_width_box->setValue(filter->maxWidth);
    _min_height_box->setValue(filter->minHeight);
    _max_height_box->setValue(filter->maxHeight);
    setCurrentRating(filter->minRating);
}

void FilterMenu::resetFilter()
{
    filter->reset();
    updateDisplay();
}
