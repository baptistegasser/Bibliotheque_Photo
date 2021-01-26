#include "modification_window.h"
#include <iostream>

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

void Modification_window::setImage(char* path)
{
    QImage img;
    if (img.load(path))
    {
        _my_image.setPixmap(QPixmap::fromImage(img));
        _my_image.show();
    }
    else
    {
        std::cerr << "la photo est introuvable" << std::endl;
    }


}
