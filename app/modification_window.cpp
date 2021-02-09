#include "modification_window.h"
#include "tagbutton.h"
#include "QInputDialog"
#include <iostream>
#include <string>
#include "QPushButton"
#include "qinputcustom.h"
#include "model/image.h"
#include "db/db.h"
#include "QSlider"
#include "QtCore"
#include "QPainter"
#include "dialogcreatetag.h"

Modification_window::Modification_window(QWidget *parent, const Image *image) :
    QWidget(parent)
{
    setupUi(this);
    img = *image;
    _my_reset->hide();
    if(img.resized)
    {
        _my_reset->show();
    }

    connect(_my_redimensionner,&QPushButton::clicked,this,&Modification_window::openResizeDialog);
    connect(_my_reset,&QPushButton::clicked,this,&Modification_window::backToOriginal);
    connect(_my_slider,&QSlider::valueChanged,this,&Modification_window::zoom);
    connect(_my_commentaire_edit,&QPlainTextEdit::textChanged,this,&Modification_window::comment);
    connect(_my_add_tag_cat_button,&QPushButton::clicked,this,&Modification_window::addTag);

    updateImage();
    this->showMaximized();

    grid_layout = new QHBoxLayout();
    area = new QWidget();
    area->setLayout(grid_layout);
    _my_categorie_tag_area->setWidget(area);

}

void Modification_window::updateImage()
{
    _my_reset->hide();

    if(img.resized)
    {
        _my_reset->show();
    }


    picture  = QPixmap(img.path);
    if(img.resized)
    {
        picture = picture.scaled(img.res_width,img.res_height);
    }
    if(img.cropped)
    {
        QRect rect (img.crop_x,img.crop_y,img.crop_width,img.crop_height);
        picture = picture.copy(rect);
    }

    _my_slider->setValue(1);
    _my_commentaire_edit->document()->setPlainText(img.comment);
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
   updateImage();
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
    updateImage();
}

void Modification_window::zoom()
{

    int val = _my_slider->value();
    int w = img.width;
    int h = img.height;
    if (img.resized)
    {
        w = img.res_width;
        h = img.res_height;
    }
    picture = picture.scaled(w*val,h*val);
    _frame.setPixmap(picture);

}

void Modification_window::comment()
{
    img.comment = _my_commentaire_edit->toPlainText();
    DB::getImageDao().save(img);
}

void Modification_window::addTag()
{
    DialogCreateTag tag;
    QString nom = tag.getName();
    QString color = tag.getColor().name();
    std::cout << nom.toStdString() << " " << color.toStdString() << std::endl;
    TagButton *tb = new TagButton(area,nom,color);
    tb->resize(tb->sizeHint().width(),tb->sizeHint().height());
    grid_layout->addWidget(tb);
}

