#ifndef DIALOGCREATETAG_H
#define DIALOGCREATETAG_H

#include "ui_dialogcreatetag.h"

class DialogCreateTag : public QDialog, private Ui::DialogCreateTag
{
    Q_OBJECT
    QString nom;
    QColor couleur;

public:
    explicit DialogCreateTag(QWidget *parent = nullptr);
    QString getName();
    QColor getColor();

public slots:
    void setName();
    void changeColor();
};

#endif // DIALOGCREATETAG_H
