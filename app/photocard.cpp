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

    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(12);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::black);
    effect->setBlurRadius(10);

    ui->photo->setGraphicsEffect(effect);

    setAttribute(Qt::WA_TranslucentBackground);
    ui->main_widget->setGraphicsEffect(effect);

    /*
    for(int i(0); i < image->feelingTags.size(); i++){
        TagButton * tagbutton = new TagButton(nullptr);
        tagbutton->setTag(image->feelingTags[i]);
        layout->addWidget(tagbutton);
    }
    */

}

void photoCard::setImage(Image *image)
{
    this->image = image;
    int height = image->height;
    int width = image->width;
    float ratio = height/width;
    ui->photo->setMinimumHeight(ui->photo->width()*ratio+30);
    ui->photo->setStyleSheet("border-image: url('"+image->path+"') 0 0 0 0 stretch stretch;");

    QVector<int> rgb = this->image->main_color;
    ui->main_color_frame->setStyleSheet("border-image: none; background-color: rgb("+QString::number(rgb[0])+','+QString::number(rgb[1])+','+QString::number(rgb[2])+")");

    ui->date_label->setText(this->image->name);
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


    TagButton * tagbutton = new TagButton(area);
    TagButton * tagbutton2 = new TagButton(area);
    TagButton * tagbutton3 = new TagButton(area);
    TagButton * tagbutton4 = new TagButton(area);

    tagbutton->setMinimumWidth(70);
    tagbutton2->setMinimumWidth(70);
    tagbutton3->setMinimumWidth(70);
    tagbutton4->setMinimumWidth(70);



    grid_layout->addWidget(tagbutton);
    grid_layout->addWidget(tagbutton2);
    grid_layout->addWidget(tagbutton3);
    grid_layout->addWidget(tagbutton4);

    area->setLayout(grid_layout);
    ui->desc_scroll->setWidget(area);
}

void photoCard::showFeelingTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();


    TagButton * tagbutton = new TagButton(area);
    TagButton * tagbutton2 = new TagButton(area);
    TagButton * tagbutton3 = new TagButton(area);
    TagButton * tagbutton4 = new TagButton(area);

    tagbutton->setMinimumWidth(70);
    tagbutton2->setMinimumWidth(70);
    tagbutton3->setMinimumWidth(70);
    tagbutton4->setMinimumWidth(70);



    grid_layout->addWidget(tagbutton);
    grid_layout->addWidget(tagbutton2);
    grid_layout->addWidget(tagbutton3);
    grid_layout->addWidget(tagbutton4);

    area->setLayout(grid_layout);
    ui->ress_scroll->setWidget(area);
}

void photoCard::showCategoryTags(){
    QHBoxLayout * grid_layout = new QHBoxLayout();
    QWidget * area = new QWidget();


    TagButton * tagbutton = new TagButton(area);
    TagButton * tagbutton2 = new TagButton(area);
    TagButton * tagbutton3 = new TagButton(area);
    TagButton * tagbutton4 = new TagButton(area);

    tagbutton->setMinimumWidth(70);
    tagbutton2->setMinimumWidth(70);
    tagbutton3->setMinimumWidth(70);
    tagbutton4->setMinimumWidth(70);



    grid_layout->addWidget(tagbutton);
    grid_layout->addWidget(tagbutton2);
    grid_layout->addWidget(tagbutton3);
    grid_layout->addWidget(tagbutton4);

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
