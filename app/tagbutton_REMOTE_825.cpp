#include "tagbutton.h"


TagButton::TagButton(QWidget *parent):QPushButton(parent)
{
    QString color = "rgb(255,0,0)";
    this->setStyleSheet("background-color:white;color:"+color+";border:1px solid red;border-radius:10px;");
    this->setFixedHeight(25);
    this->setText("Test");
}
