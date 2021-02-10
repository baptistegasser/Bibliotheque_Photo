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

    connect(_my_redimensionner,&QPushButton::clicked,this,&Modification_window::openResizeDialog);
    connect(_my_reset,&QPushButton::clicked,this,&Modification_window::backToOriginal);
    connect(_my_slider,&QSlider::valueChanged,this,&Modification_window::zoom);
    connect(_my_commentaire_edit,&QPlainTextEdit::textChanged,this,&Modification_window::comment);
    connect(_my_add_tag_cat_button,&QPushButton::clicked,this,[=](){this->addTag(0);});
    connect(_my_add_tag_desc_button,&QPushButton::clicked,this,[=](){this->addTag(1);});
    connect(_my_add_tag_ress_button,&QPushButton::clicked,this,[=](){this->addTag(2);});


    updateImage();
    initLayout();
    initDetail();
    this->showMaximized();

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

void Modification_window::initLayout()
{
    grid_layout_cat = new FlowLayout();
    area_cat = new QWidget();
    area_cat->setLayout(grid_layout_cat);
    _my_categorie_tag_area->setWidget(area_cat);

    grid_layout_feel = new FlowLayout();
    area_feel = new QWidget();
    area_feel->setLayout(grid_layout_feel);
    _my_ressenti_tag_area->setWidget(area_feel);

    grid_layout_desc = new FlowLayout();
    area_desc = new QWidget();
    area_desc->setLayout(grid_layout_desc);
    _my_descriptif_tag_area->setWidget(area_desc);
}

void Modification_window::initDetail()
{
    //_my_color_dominant_edit->setText(img.main_color);
    _my_commentaire_edit->document()->setPlainText(img.comment);
    QVector<Tag> catTag = img.categoryTags.toVector();
    for(Tag &t:catTag)
    {
        TagButton *tb = getTagButtonFromTag(t);
        grid_layout_cat->addWidget(tb);
    }
    QVector<Tag> feelTag = img.feelingTags.toVector();
    for(Tag &t:feelTag)
    {
        TagButton *tb = getTagButtonFromTag(t);
        grid_layout_feel->addWidget(tb);
    }


    QVector<Tag> descTag = img.descriptiveTags.toVector();
//    int row = grid_layout_desc->rowCount();
//    int col = 0;
    for(Tag &t:descTag)
    {
        TagButton *tb = getTagButtonFromTag(t);
        /*f (grid_layout_desc->count()% 4 == 0)
        {
            row++;
            col = 0;
        }*/
        grid_layout_desc->addWidget(tb);
//        col++;
    }

}

void Modification_window::addTag(int i)
{
    QWidget * area;
    FlowLayout * layout;
    QList<Tag> * list;
    switch (i) {
        case 0:
            area = area_cat;
            layout = grid_layout_cat;
            list = &img.categoryTags;
            break;
        case 1:
            area = area_desc;
            layout = grid_layout_desc;
            list = &img.descriptiveTags;
            break;
        case 2:
            area = area_feel;
            layout = grid_layout_feel;
            list = &img.feelingTags;
            break;

    }
    DialogCreateTag tag;
    if (tag.getIsDone())
    {
        QString nom = tag.getName();
        QString color = tag.getColor().name();
        TagButton *tb = new TagButton(area,nom,color);
        if(!list->contains(Tag(nom,color)))
        {
            layout->addWidget(tb);
            list->append(Tag(nom,color));
            DB::getImageDao().save(img);
        }
    }
}

TagButton *Modification_window::getTagButtonFromTag(Tag tag)
{
    TagButton *tb = new TagButton (nullptr,tag.value,tag.color);
    return tb;
}

