#include "photocard.h"
#include "ui_photocard.h"
#include "tagbutton.h"

#include <iostream>
#include <QGraphicsDropShadowEffect>

photoCard::photoCard(QWidget *parent, Image *image) :
    QWidget(parent),
    ui(new Ui::photoCard)
{
    this->image = image;
    ui->setupUi(this);

    //if (img.load(image->path)) ui->photo->setStyleSheet("background-image: url('"+image->path+"')");

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

    TagButton * tagbutton = new TagButton(nullptr);
    TagButton * tagbutton2 = new TagButton(nullptr);
    TagButton * tagbutton3 = new TagButton(nullptr);
    TagButton * tagbutton4 = new TagButton(nullptr);

    tagbutton->setMinimumWidth(70);
    tagbutton2->setMinimumWidth(70);
    tagbutton3->setMinimumWidth(70);
    tagbutton4->setMinimumWidth(70);

    QScrollArea * area_scroll = new QScrollArea( ui->desc_frame );
    area_scroll->setGeometry(0, 0, 250, 40);
    area_scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area_scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    area_scroll->setWidgetResizable(true);

    QWidget *area = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(area);

    area_scroll->setWidget(area);

    /*
    for(int i(0); i < image->feelingTags.size(); i++){
        TagButton * tagbutton = new TagButton(nullptr);
        tagbutton->setTag(image->feelingTags[i]);
        layout->addWidget(tagbutton);
    }
    */

    layout->addWidget(tagbutton);
    layout->addWidget(tagbutton2);
    layout->addWidget(tagbutton3);
    layout->addWidget(tagbutton4);
}

photoCard::~photoCard()
{
    delete ui;
}
