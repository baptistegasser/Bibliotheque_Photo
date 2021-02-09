#include "tagbutton.h"


TagButton::TagButton(QWidget *parent)
{
    this->setStyleSheet("background-color:white;color:red ;border:solid red ;border-width: 1px 1px 1px 1px;border-radius:10px;");
    this->setFixedHeight(20);
    this->setFixedWidth(30);
    this->setText("Test");
}

TagButton::TagButton(QWidget *parent,QString name,QString color):QPushButton(parent)
{
    this->setStyleSheet("background-color:white;color:"+color+";border:solid "+color+";border-width: 1px 1px 1px 1px;border-radius:10px;");
    this->setFixedHeight(20);
    this->setFixedWidth(30);
    this->setText(name);
}


