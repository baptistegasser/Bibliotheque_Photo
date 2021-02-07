#include "modification_window.h"
#include "tagbutton.h"
#include "QInputDialog"
#include <iostream>
#include <string>
#include "QPushButton"
#include "qinputcustom.h"
#include "model/image.h"
#include "db/db.h"

Modification_window::Modification_window(QWidget *parent, const Image *image) :
    QWidget(parent)
{
    setupUi(this);
    img = *image;

    //_frame.setMaximumHeight(800);
    //_frame.setMaximumWidth(1400);


    _my_reset->hide();
    if(img.resized)
    {
        _my_reset->show();
    }

    connect(_my_redimensionner,&QPushButton::clicked,this,&Modification_window::openResizeDialog);
    connect(_my_reset,&QPushButton::clicked,this,&Modification_window::backToOriginal);

    setImage();

    this->showMaximized();


}

void Modification_window::setImage()
{
    _my_reset->hide();
    if(img.resized)
    {
        _my_reset->show();
    }


    QPixmap picture (img.path);
    if(img.resized)
    {
        picture = picture.scaled(img.res_width,img.res_height);
    }
    if(img.cropped)
    {
        QRect rect (img.crop_x,img.crop_y,img.crop_width,img.crop_height);
        picture = picture.copy(rect);
    }

    _frame.setPixmap(picture);
    _frame.setAlignment(Qt::AlignCenter);
    _my_picture->setWidget(&_frame);
    _frame.show();
}

void Modification_window::resizeImage(int w, int h)
{
   img.res_height = h;
   img.res_width = w;
   img.resized = true;
   DB::getImageDao().save(img);
   setImage();



}

void Modification_window::openResizeDialog()
{
    int preWidth = img.width;
    int preHeight = img.height;
    if(img.resized)
    {
        preHeight = img.res_height;
        preWidth = img.res_width;
    }
    QInputCustom input(this,2,{"Largeur","Hauteur"},{QString::number(preWidth),QString::number(preHeight)});
    QStringList list = input.getStrings();
    resizeImage(list[0].toInt(),list[1].toInt());
}

void Modification_window::backToOriginal()
{
    img.resized = false;
    img.cropped = false;
    DB::getImageDao().save(img);
    setImage();
}
