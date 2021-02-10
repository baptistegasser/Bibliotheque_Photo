#ifndef FILTERMENU_H
#define FILTERMENU_H

#include "ui_filtermenu.h"
#include "db/filter.h"
#include <QList>
#include <QMenu>
#include <QPushButton>

class FilterMenu : public QMenu, private Ui::FilterMenu
{
    Q_OBJECT

private:
    Filter *filter;
    double currentRating;
    QList<QPushButton *> stars;
    void setCurrentRating(int rating);
    void updateDisplay();

private slots:
    void resetFilter();

public:
    explicit FilterMenu(Filter *filter, QWidget *parent = nullptr);
    void updateFilter();

signals:
    void filterUpdated();
};

#endif // FILTERMENU_H
