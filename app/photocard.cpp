#include "photocard.h"
#include "ui_photocard.h"

#include <QGraphicsDropShadowEffect>

photoCard::photoCard(QWidget *parent, Image *image) :
    QWidget(parent),
    ui(new Ui::photoCard)
{
    this->image = image;
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
}

photoCard::~photoCard()
{
    delete ui;
}
