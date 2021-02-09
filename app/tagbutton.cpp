#include "tagbutton.h"


TagButton::TagButton(QWidget *parent)
{
    this->setText("Test");
    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setText("Test");
     this->setStyleSheet("background-color:white;color:red ;border:solid red ;border-width: 1px 1px 1px 1px;border-radius:10px;");
}

TagButton::TagButton(QWidget *parent,QString name,QString color):QPushButton(parent)
{
    this->setText(name);
    this->setFixedWidth(this->sizeHint().width());
    this->setFixedHeight(this->sizeHint().height());
    this->setStyleSheet("background-color:white;color:"+color+";border:solid "+color+";border-width: 1px 1px 1px 1px;border-radius:10px;");
}


