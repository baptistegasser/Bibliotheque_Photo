#include "photocard.h"
#include "ui_photoCard.h"

#include <QGraphicsDropShadowEffect>

photoCard::photoCard(QWidget *parent, Image *image) :
    QWidget(parent),
    ui(new Ui::photoCard)
{
    this->image = image;
    ui->setupUi(this);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(20);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::black);


    ui->photo->setGraphicsEffect(effect);
}

photoCard::~photoCard()
{
    delete ui;
}
