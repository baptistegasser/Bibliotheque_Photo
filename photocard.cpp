#include "photocard.h"
#include "ui_photoCard.h"

#include <QGraphicsDropShadowEffect>

photoCard::photoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoCard)
{
    ui->setupUi(this);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(10);
    effect->setXOffset(0);
    effect->setYOffset(0);
    effect->setColor(Qt::black);

    ui->photo->setGraphicsEffect(effect);
}

photoCard::~photoCard()
{
    delete ui;
}
