#ifndef DIALOGCREATETAG_H
#define DIALOGCREATETAG_H

#include "ui_dialogcreatetag.h"

class DialogCreateTag : public QDialog, private Ui::DialogCreateTag
{
    Q_OBJECT
    QString nom;
    QColor couleur;
    bool isDone;


public:
    explicit DialogCreateTag(QWidget *parent = nullptr);
    QString getName();
    QColor getColor();
    bool getIsDone();

public slots:
    void setName();
    void changeColor();
    void accept();
    void reject();
};

#endif // DIALOGCREATETAG_H
