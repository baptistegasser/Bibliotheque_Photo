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
#include "QRgb"
#include "QRadioButton"
#include "QFileDialog"
#include "resizable_rubber_rand.h"

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
    connect(_my_download_button,&QPushButton::clicked,this,&Modification_window::save);
    connect(_my_recadrer,&QPushButton::clicked,this,&Modification_window::cropped);
    updateImage();
    initLayout();
    initDetail();
    this->showMaximized();

}

/**
 * Update the image after modification
 * @brief Modification_window::updateImage
 */
void Modification_window::updateImage()
{
    _my_reset->hide();
    if(img.resized || img.cropped)
    {
        _my_reset->show();
    }
    picture  = QPixmap(img.path);
    if(img.cropped)
    {
        _my_recadrer->hide();
        QRect rect (img.crop_x,img.crop_y,img.crop_width,img.crop_height);
        picture = picture.copy(rect);
    }
    if(img.resized)
    {
        picture = picture.scaled(img.res_width,img.res_height);
    }
    _my_slider->setValue(1);
    if(img.resized)
    {
        _frame.setGeometry((_my_picture->width()/2)-(img.res_width/2),(_my_picture->height()/2)-(img.res_height/2),img.res_width,img.res_height);
        _frame.setFixedSize(QSize(img.res_width,img.res_height));
    }
    else
    {
        _frame.setGeometry((_my_picture->width()/2)-(img.width/2),(_my_picture->height()/2)-(img.height/2),img.width,img.height);
        _frame.setFixedSize(QSize(img.width,img.height));
    }
    _frame.setPixmap(picture);
    _frame.setAlignment(Qt::AlignCenter);
    _my_picture->setWidget(&_frame);
    _my_picture->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    _frame.show();
}

/**
 * Permite to resize the photo with parameter
 * @brief Modification_window::resizeImage
 * @param w
 * @param h
 */
void Modification_window::resizeImage(int w, int h)
{
    if(ratio)
    {
        if(img.resized)
        {
            picture = picture.scaled(img.width,img.height);
            if(w > img.res_width || h > img.res_height)
            {
                picture = picture.scaled(w,h,Qt::KeepAspectRatioByExpanding);
            }
            else
            {
                picture = picture.scaled(w,h,Qt::KeepAspectRatio);
            }
        }
        else
        {
            if(w > img.width || h > img.height)
            {
                picture = picture.scaled(w,h,Qt::KeepAspectRatioByExpanding);
            }
            else
            {
                picture = picture.scaled(w,h,Qt::KeepAspectRatio);
            }
        }
    }
    else
    {
        picture = picture.scaled(w,h);
    }
    img.res_height = picture.height();
    img.res_width = picture.width();
    img.resized = true;
    DB::getImageDao().save(img);
    updateImage();
}

/**
 * Access to the photo resize window
 * @brief Modification_window::openResizeDialog
 */
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
    QRadioButton ratio ("garder le ratio");
    input.addWidget(&ratio);
    input.exec();
    if(input.isDone())
    {
        QStringList list = input.getStrings();
        this->ratio = ratio.isChecked();
        resizeImage(list[0].toInt(),list[1].toInt());
    }
}

/**
 * Permite to return to the original photo
 * @brief Modification_window::backToOriginal
 */
void Modification_window::backToOriginal()
{
    img.resized = false;
    img.cropped = false;
    _my_recadrer->show();
    DB::getImageDao().save(img);
    updateImage();
}

/**
 * Permit to zoom on the photo
 * @brief Modification_window::zoom
 */
void Modification_window::zoom()
{

    int val = _my_slider->value();
    if (val != 1)
    {
        isZoomed = true;
    }
    else
    {
        isZoomed = false;
    }
    int w = img.width;
    int h = img.height;
    if (img.resized)
    {
        w = img.res_width;
        h = img.res_height;
    }
    picture = picture.scaled(w*val,h*val);
    _frame.setPixmap(picture);
    _frame.setFixedSize(QSize(w*val,h*val));
    _frame.setGeometry((_my_picture->width()/2)-(w*val/2),(_my_picture->height()/2)-(h*val/2),w*val,h*val);


}

/**
 * Add a comment to the photo
 * @brief Modification_window::comment
 */
void Modification_window::comment()
{
    img.comment = _my_commentaire_edit->toPlainText();
    DB::getImageDao().save(img);
}

/**
 * Init the layout
 * @brief Modification_window::initLayout
 */
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
    _my_picture_label->setText(img.name);
    _my_picture_label->setStyleSheet("font:25px");
    _my_picture_label->setAlignment(Qt::AlignCenter);

    _my_color_dominant_edit->setEnabled(false);
    QColor domCol (img.main_color.at(0),img.main_color.at(1),img.main_color.at(2));
    _my_color_dominant_edit->setText(domCol.name());
    _my_color_dominant_edit->setStyleSheet("background-color:"+domCol.name()+";");

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
    for(Tag &t:descTag)
    {
        TagButton *tb = getTagButtonFromTag(t);
        grid_layout_desc->addWidget(tb);
    }
    for (int i = 0; i< 5 ;i++ )
    {
        QIcon icon;
        if (i <= img.rating-1)
        {
            icon.addPixmap(QPixmap(":/image/star_full").scaled(200,200));
        }
        else
        {
            icon.addPixmap(QPixmap(":/image/star_empty").scaled(200,200));
        }
        QPushButton * button = new QPushButton(icon,"");
        button->setStyleSheet("border:none;background-color:rgb(250,250,250);");
        connect(button,&QPushButton::clicked,this,[=](){this->changeNote(i);});
        _my_rating_layout->addWidget(button);
        stars.append(button);

    }
}

/**
 * Add one tag to the photo
 * @brief Modification_window::addTag
 * @param i
 */
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

/**
 * Update rate of the photo
 * @brief Modification_window::changeNote
 * @param rating
 */
void Modification_window::changeNote(int rating)
{
    if (rating == img.rating-1)
    {
        rating--;
    }
    for (int i = 0; i < 5; ++i) {
        if (rating >= i) {
            stars.at(i)->setIcon(QIcon(":/image/star_full"));
        } else {
            stars.at(i)->setIcon(QIcon(":/image/star_empty"));
        }
    }
    img.rating = rating+1;
    DB::getImageDao().save(img);
}

QPushButton *Modification_window::getReturnButton()
{
    return _my_return_button;
}

void Modification_window::save()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),img.name,tr("Images (*.png *.jpeg *.jpg)"));
    picture.save(fileName);
}

void Modification_window::cropped ()
{
    updateImage();
    Resizable_rubber_band * band = new Resizable_rubber_band(&_frame);
    if (img.resized)
    {
        band->move((_frame.width()/2)-(img.res_width/2),(_frame.height()/2)-(img.res_height/2));
    }
    else if (img.cropped)
    {
        band->move((_frame.width()/2)-(img.crop_width/2),(_frame.height()/2)-(img.crop_height/2));
    }
    else
    {
        band->move((_frame.width()/2)-(img.width/2),(_frame.height()/2)-(img.height/2));
    }

    band->setStyleSheet("background-color:rgba(0,0,200,0.5);");
    band->resize(50,50);
    if(img.resized)
    {
        band->setMaximumHeight(img.res_height);
        band->setMaximumWidth(img.res_width);
    }
    else if (img.cropped)
    {
        band->setMaximumHeight(img.crop_height);
        band->setMaximumWidth(img.crop_width);
    }
    else
    {
        band->setMaximumHeight(img.height);
        band->setMaximumWidth(img.width);
    }

    band->setMinimumSize(30,30);

    _my_detail_box->setEnabled(false);
    groupBox->setEnabled(false);
    _my_download_button->setEnabled(false);
    _my_slider->setEnabled(false);
    _my_return_button->setEnabled(false);

    croppAccept = new QPushButton("Recadrer");
    croppAccept->setFixedSize(200,50);
    croppAccept->setStyleSheet("background-color:white;color:black ;border:solid darkgrey ;border-width: 1px 1px 1px 1px;border-radius:10px;");
    croppCancel = new QPushButton("Annuler");
    croppCancel->setStyleSheet("background-color:white;color:black ;border:solid darkgrey ;border-width: 1px 1px 1px 1px;border-radius:10px;");
    croppCancel->setFixedSize(200,50);
    _cropp_layout->setAlignment(Qt::AlignHCenter);
    _cropp_layout->addWidget(croppAccept);
    _cropp_layout->addWidget(croppCancel);



    croppAccept->show();
    connect(croppAccept,&QPushButton::clicked,this,[=](){band->hide();this->toCrop(band->frameGeometry());});
    connect(croppCancel,&QPushButton::clicked,this,[=](){band->hide();this->cropCancel();});

}

void Modification_window::toCrop(QRect rect)
{

    img.cropped = true;
    img.crop_x = rect.x();
    img.crop_y = rect.y();
    img.crop_width = rect.width();
    img.crop_height = rect.height();



    _my_detail_box->setEnabled(true);
    groupBox->setEnabled(true);
    _my_download_button->setEnabled(true);
    _my_slider->setEnabled(true);
    _my_return_button->setEnabled(true);

    DB::getImageDao().save(img);
    updateImage();
    delete croppAccept;
    delete croppCancel;
}

void Modification_window::cropCancel()
{
    _my_detail_box->setEnabled(true);
    groupBox->setEnabled(true);
    _my_download_button->setEnabled(true);
    _my_slider->setEnabled(true);
    _my_return_button->setEnabled(true);
    delete croppAccept;
    delete croppCancel;
}

