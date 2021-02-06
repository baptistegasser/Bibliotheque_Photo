#ifndef PHOTOCARD_H
#define PHOTOCARD_H

#include <QWidget>
#include "model/image.h"

namespace Ui {
class photoCard;
}

class photoCard : public QWidget
{
    Q_OBJECT

public:
    photoCard(QWidget *parent = nullptr);
    void setImage(Image *image);
    ~photoCard();

private:
    Ui::photoCard *ui;
    Image *image;
};

#endif // PHOTOCARD_H
