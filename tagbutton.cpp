#include "tagbutton.h"


TagButton::TagButton()
{
    QString color = "(255,0,0)";
    this->setStyleSheet("height:10px;background-color:white;color:"+color+";border-color:"+color+";");
    this->setText("Test");
}
