#include "dialogcreatetag.h"
#include "QColorDialog"
#include "db/db.h"
#include <iostream>

DialogCreateTag::DialogCreateTag(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);
    if(_label_colo->text() == "Non sélectionnée" || _my_combo->currentText().isEmpty())
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    _my_frame->setStyleSheet("border:1px solid black;");
    connect(_my_combo,&QComboBox::editTextChanged,this,&DialogCreateTag::setName);
    connect(_my_button_color,&QPushButton::clicked,this,&DialogCreateTag::changeColor);
    isClear = true;
    exec();
}

void DialogCreateTag::setName()
{

    QStringList alreadySet ;
    for (int i = 0;i < _my_combo->count() ;i++ ) {
        alreadySet.append(  _my_combo->itemText(i));
    }
    QList<Tag> list = DB::getTagDao().search(_my_combo->currentText());
    for(const Tag &t : qAsConst(list) ) {
        if(!alreadySet.contains(t.value))
        {
            _my_combo->addItem(t.value);
        }
    }
    nom = _my_combo->currentText();
    if (DB::getTagDao().exist(nom))
    {
        QString color = DB::getTagDao().getByValue(nom).color;
        QColor col = QColor(color);
        _my_frame->setPalette(QPalette(col));
        _my_frame->setAutoFillBackground(true);
        _label_colo->setText(col.name());
        _my_button_color->hide();

    }
    else
    {
        _my_frame->setAutoFillBackground(false);
        _my_button_color->show();
        _label_colo->setText("Non sélectionnée");
    }
    if(_label_colo->text() != "Non sélectionnée" && !_my_combo->currentText().isEmpty())
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

void DialogCreateTag::changeColor()
{

    QColorDialog dialog(this);
    couleur = dialog.getColor();
    _my_frame->setPalette(QPalette(couleur));
    _my_frame->setAutoFillBackground(true);
    _label_colo->setText(couleur.name());
    if(_label_colo->text() != "Non sélectionnée" && !_my_combo->currentText().isEmpty())
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }
    else
    {
        buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
}

QString DialogCreateTag::getName()
{
    return nom;
}

QColor DialogCreateTag::getColor()
{
    return couleur;
}


