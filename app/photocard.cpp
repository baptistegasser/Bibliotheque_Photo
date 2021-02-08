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

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::black);

    ui->photo->setGraphicsEffect(effect);

    /*
    QScrollArea * area_scroll = new QScrollArea( ui->desc_frame );
    area_scroll->setGeometry(0, 0, 200, 40);
    area_scroll->setWidgetResizable(true);

    QHBoxLayout * layout = new QHBoxLayout(area);

    layout->setGeometry(QRect(0,0, 300, 50));

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
    ui->photo->setStyleSheet("border-image: url("+image->path+") 0 0 0 0 stretch stretch;");

    QVector<int> rgb = this->image->main_color;
    ui->main_color_frame->setStyleSheet("border-image: none; background-color: rgb("+QString::number(rgb[0])+','+QString::number(rgb[1])+','+QString::number(rgb[2])+")");

    showDescriptionTags();
    showRateStars();

}


void photoCard::showDescriptionTags()
{
    QHBoxLayout * grid_layout = new QHBoxLayout();
    //QWidget * area = new QWidget();


    TagButton * tagbutton = new TagButton(ui->scrollAreaWidgetContents);
    TagButton * tagbutton2 = new TagButton(ui->scrollAreaWidgetContents);
    TagButton * tagbutton3 = new TagButton(ui->scrollAreaWidgetContents);
    TagButton * tagbutton4 = new TagButton(ui->scrollAreaWidgetContents);
    TagButton * tagbutton5 = new TagButton(ui->scrollAreaWidgetContents);
    TagButton * tagbutton6 = new TagButton(ui->scrollAreaWidgetContents);

    tagbutton->setMinimumWidth(70);
    tagbutton2->setMinimumWidth(70);
    tagbutton3->setMinimumWidth(70);
    tagbutton4->setMinimumWidth(70);
    tagbutton5->setMinimumWidth(70);
    tagbutton6->setMinimumWidth(70);



    grid_layout->addWidget(tagbutton);
    grid_layout->addWidget(tagbutton2);
    grid_layout->addWidget(tagbutton3);
    grid_layout->addWidget(tagbutton4);
    grid_layout->addWidget(tagbutton5);
    grid_layout->addWidget(tagbutton6);


    //ui->desc_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->desc_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->scrollAreaWidgetContents->setLayout(grid_layout);
    ui->desc_scroll->setWidget(ui->scrollAreaWidgetContents);
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
