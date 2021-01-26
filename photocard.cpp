#include "photocard.h"
#include "ui_photocard.h"

photoCard::photoCard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::photoCard)
{
    ui->setupUi(this);
}

photoCard::~photoCard()
{
    delete ui;
}
