#ifndef TAGBUTTON_H
#define TAGBUTTON_H

#include "QPushButton"
#include "model/tag.h"

class TagButton : public QPushButton
{

public:
    TagButton(QWidget * parent);
    void setTag(Tag* tag);
};

#endif // TAGBUTTON_H
