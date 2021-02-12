#include "tagbutton.h"


TagButton::TagButton(QWidget *parent,QString name,QString color):QPushButton(parent)
{
    this->setText(name);
    this->setFixedHeight(this->sizeHint().height()+5);
    this->setStyleSheet("background-color:white;color:rgb(120,120,120);border:solid "+color+";border-width: 2px 2px 2px 2px;border-radius:10px;font-size:14px;padding-left:5px;padding-right:5px;");
}


