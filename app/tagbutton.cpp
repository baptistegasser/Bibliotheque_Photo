#include "tagbutton.h"


TagButton::TagButton(QWidget *parent):QPushButton(parent)
{
    QString color = "rgb(255,0,0)";
    this->setStyleSheet("background-color:white;color:"+color+";border:solid 1px black;border-radius:10px;");
    this->setFixedHeight(20);
    this->setText("Test");
}

void TagButton::setTag(Tag* tag){
    this->setStyleSheet("background-color:white;color:"+tag->color+";border:solid 1px black;border-radius:10px;");
    this->setText(tag->value);
}

