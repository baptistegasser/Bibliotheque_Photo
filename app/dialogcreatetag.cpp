#include "dialogcreatetag.h"
#include "QColorDialog"
#include "db/db.h"
#include <iostream>
#include "QCompleter"

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
    exec();

}

/**
 * Set the name when text was edit
 * @brief DialogCreateTag::setName
 */
void DialogCreateTag::setName()
{
    QStringList wordList;
    QList<Tag> list = DB::getTagDao().search(_my_combo->currentText());
    for(const Tag &t : qAsConst(list) ) {
        wordList.append(t.value);
    }
    QCompleter * completer = new QCompleter(wordList,_my_combo);
    _my_combo->setCompleter(completer);
    nom = _my_combo->currentText();
    if (DB::getTagDao().exist(nom))
    {
        QString color = DB::getTagDao().getByValue(nom).color;
        couleur = QColor(color);
        _my_frame->setPalette(QPalette(couleur));
        _my_frame->setAutoFillBackground(true);
        _label_colo->setText(couleur.name());
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

/**
 * Change the background color of the tag
 * @brief DialogCreateTag::changeColor
 */
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

bool DialogCreateTag::getIsDone()
{
    return this->isDone;
}

void DialogCreateTag::accept()
{
    this->isDone = true;
    QDialog::accept();
}

void DialogCreateTag::reject()
{
    this->isDone = false;
    QDialog::reject();
}
