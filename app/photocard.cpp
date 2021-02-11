#include "photocard.h"
#include "ui_photocard.h"
#include "tagbutton.h"

#include <iostream>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QImage>
#include <QDebug>
#include <QMouseEvent>

PhotoCard::PhotoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PhotoCard)
{
    ui->setupUi(this);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(20);
    effect->setXOffset(-.1);
    effect->setYOffset(0);
    QColor color = QColor(0,0,0,50);
    effect->setColor(color);

    ui->main_widget->setGraphicsEffect(effect);
    ui->main_widget->setStyleSheet("background-color: #FFFFFF");
    setAttribute(Qt::WA_TranslucentBackground);

    isClicked = false;
}

void PhotoCard::setImage(Image *image)
{
    this->image = image;
    int height = image->height;
    int width = image->width;
    float ratio = (float)height/width;
    ui->photo->setMinimumHeight(ui->photo->width()*ratio);
    QLabel *container = new QLabel(ui->photo);
    container->setPixmap(QPixmap(image->path).scaled(ui->photo->width(), ui->photo->height()*ratio));


    QVector<int> rgb = this->image->main_color;
    ui->main_color_frame->setStyleSheet("border-image: none; background-color: rgb("+QString::number(rgb[0])+','+QString::number(rgb[1])+','+QString::number(rgb[2])+")");

    ui->date_label->setStyleSheet("font-size: 11px;");
    QFontMetrics metrics(ui->date_label->font());
    QString elidedText = metrics.elidedText(this->image->name, Qt::ElideRight, ui->photo->width());
    ui->date_label->setText(elidedText);
    ui->info_label->setText(QString::number(this->image->size/8000)+"Ko");

    showDescriptiveTags();
    showFeelingTags();
    showCategoryTags();
    showRateStars();
}


void PhotoCard::showDescriptiveTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->descriptiveTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->descriptiveTags[i].value, image->descriptiveTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    if(image->descriptiveTags.size() == 0){
        QLabel *no_tag = new QLabel("Auncun tag descriptif");
        no_tag->setStyleSheet("font-style: italic; color: #B3B2B2;");
        grid_layout->addWidget(no_tag);
    }

    area->setLayout(grid_layout);
    ui->desc_scroll->setWidget(area);
    ui->desc_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->desc_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PhotoCard::showFeelingTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->feelingTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->feelingTags[i].value, image->feelingTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    if(image->feelingTags.size() == 0){
        QLabel *no_tag = new QLabel("Auncun tag de ressenti");
        no_tag->setStyleSheet("font-style: italic; color: #B3B2B2;");
        grid_layout->addWidget(no_tag);
    }

    area->setLayout(grid_layout);
    ui->ress_scroll->setWidget(area);
    ui->ress_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->ress_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void PhotoCard::showCategoryTags(){
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->categoryTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->categoryTags[i].value, image->categoryTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    if(image->categoryTags.size() == 0){
        QLabel *no_tag = new QLabel("Auncun tag mot-clé");
        no_tag->setStyleSheet("font-style: italic; color: #B3B2B2;");
        grid_layout->addWidget(no_tag);
    }

    area->setLayout(grid_layout);
    ui->keyw_scroll->setWidget(area);
    ui->keyw_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->keyw_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}


void PhotoCard::showRateStars()
{
    QList<QPushButton *> stars = {
        ui->star_1,
        ui->star_2,
        ui->star_3,
        ui->star_4,
        ui->star_5
    };

    for (int i = 0; i < 5; ++i) {
        if (i+1 <= image->rating) {
            stars[i]->setIcon(QIcon(":/image/star_full"));
        } else {
            stars[i]->setIcon(QIcon(":/image/star_empty"));
        }
    }
}

void PhotoCard::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (isClicked) {
            isClicked = false;
            emit clicked(this);
        } else {
            emit isSelectionned(this);
        }
    }
}

PhotoCard::~PhotoCard()
{
    delete ui;
}

Image* PhotoCard::getImage()
{
    return image;
}

Ui::PhotoCard *PhotoCard::getUi()
{
    return ui;
}

void PhotoCard::setIsClicked(bool b)
{
    this->isClicked = b;
}

bool PhotoCard::getIsClicked()
{
    return isClicked;
}
