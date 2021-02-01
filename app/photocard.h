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
    explicit photoCard(QWidget *parent = nullptr, Image *image = nullptr);
    ~photoCard();

private:
    Ui::photoCard *ui;
    Image *image;
};

#endif // PHOTOCARD_H
