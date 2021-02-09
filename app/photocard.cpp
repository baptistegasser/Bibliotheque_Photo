#include "photocard.h"
#include "ui_photocard.h"
#include "tagbutton.h"

#include <iostream>
#include <QGraphicsDropShadowEffect>
#include <QPixmap>
#include <QImage>
#include <QDebug>

photoCard::photoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoCard)
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
}

void photoCard::setImage(Image *image)
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


void photoCard::showDescriptiveTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->descriptiveTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->descriptiveTags[i].value, image->descriptiveTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    area->setLayout(grid_layout);
    ui->desc_scroll->setWidget(area);
    ui->desc_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->desc_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void photoCard::showFeelingTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->feelingTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->feelingTags[i].value, image->feelingTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    area->setLayout(grid_layout);
    ui->ress_scroll->setWidget(area);
}

void photoCard::showCategoryTags(){
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();

    for(int i(0); i < image->categoryTags.size(); i++){
        TagButton * tagbutton = new TagButton(area, image->categoryTags[i].value, image->categoryTags[i].color);
        grid_layout->addWidget(tagbutton);
    }

    area->setLayout(grid_layout);
    ui->keyw_scroll->setWidget(area);
}


void photoCard::showRateStars()
{
    QString fill = "border-image: url(:/image/resources/star_fill.png) 0 0 0 0 stretch stretch;";
    switch (image->rating) {
        case 1:
            ui->star1_frame->setStyleSheet(fill);
            break;
        case 2:
            ui->star1_frame->setStyleSheet(fill);
            ui->star2_frame->setStyleSheet(fill);
            break;
        case 3:
            ui->star1_frame->setStyleSheet(fill);
            ui->star2_frame->setStyleSheet(fill);
            ui->star3_frame->setStyleSheet(fill);
            break;
        case 4:
            ui->star1_frame->setStyleSheet(fill);
            ui->star2_frame->setStyleSheet(fill);
            ui->star3_frame->setStyleSheet(fill);
            ui->star4_frame->setStyleSheet(fill);
            break;
        case 5:
            ui->star1_frame->setStyleSheet(fill);
            ui->star2_frame->setStyleSheet(fill);
            ui->star3_frame->setStyleSheet(fill);
            ui->star4_frame->setStyleSheet(fill);
            ui->star5_frame->setStyleSheet(fill);
            break;
        default:
            break;
    }
}

photoCard::~photoCard()
{
    delete ui;
}
