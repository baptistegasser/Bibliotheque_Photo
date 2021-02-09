#ifndef TAGBUTTON_H
#define TAGBUTTON_H

#include "QPushButton"
#include "model/tag.h"

class TagButton : public QPushButton
{
public:
    TagButton(QWidget * parent);
    TagButton(QWidget * parent,QString name,QString color);
};

#endif // TAGBUTTON_H
