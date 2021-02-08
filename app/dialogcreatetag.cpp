#include "dialogcreatetag.h"
#include "QColorDialog"

DialogCreateTag::DialogCreateTag(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    _my_frame->setStyleSheet("border:1px solid black;");
    connect(_my_combo,&QComboBox::editTextChanged,this,&DialogCreateTag::setName);
    connect(_my_button_color,&QPushButton::clicked,this,&DialogCreateTag::changeColor);
    exec();
}

void DialogCreateTag::setName()
{
    nom = _my_combo->currentText();
}

void DialogCreateTag::changeColor()
{
    QColorDialog dialog(this);
    couleur = dialog.getColor();
    _my_frame->setPalette(QPalette(couleur));
    _my_frame->setAutoFillBackground(true);
    _label_colo->setText(couleur.name());
}

QString DialogCreateTag::getName()
{
    return nom;
}

QColor DialogCreateTag::getColor()
{
    return couleur;
}
