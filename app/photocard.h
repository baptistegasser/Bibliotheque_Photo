#ifndef PHOTOCARD_H
#define PHOTOCARD_H

#include <QWidget>
#include "model/image.h"

namespace Ui {
class PhotoCard;
}

class PhotoCard : public QWidget
{
    Q_OBJECT

public:
    PhotoCard(QWidget *parent = nullptr);
    void setImage(Image *image);
    ~PhotoCard();
    Image *getImage();
    Ui::PhotoCard *getUi();
    void setIsClicked(bool b);
    bool getIsClicked();

signals:
    void clicked(PhotoCard *ph);
    void isSelectionned(PhotoCard *ph);

private:
    Ui::PhotoCard *ui;
    Image *image;
    bool isClicked;
    void showDescriptiveTags();
    void showFeelingTags();
    void showCategoryTags();
    void showRateStars();
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // PHOTOCARD_H
