#include "modification_window.h"

Modification_window::Modification_window(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    _my_image.setParent(_my_picture);

}

void Modification_window::setImage(QImage image)
{
    _my_image.setPixmap(QPixmap::fromImage(image));
    _my_image.show();
}
