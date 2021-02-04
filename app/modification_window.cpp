#include "modification_window.h"
#include "tagbutton.h"
#include "QInputDialog"
#include <iostream>
#include <string>
#include "QPushButton"

Modification_window::Modification_window(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    _my_image.setParent(_my_picture);

    connect(_my_redimensionner,&QPushButton::clicked,this,&Modification_window::openResizeDialog);


    TagButton * tagbutton = new TagButton(nullptr);
    TagButton * tagbutton2 = new TagButton(nullptr);
    _my_layout_cat_tag->addWidget(tagbutton);
    _my_layout_cat_tag->addWidget(tagbutton2);

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

void Modification_window::setQFileInfo(QFileInfo img)
{
    this->img = img;
}

void Modification_window::resizeImage(int w, int h)
{
    //db.sentModif("resize:"+w+","+h);
    std::cout << "resize " << w << " " << h << std::endl;
}

void Modification_window::openResizeDialog()
{
  bool done;
  QString input = QInputDialog::getText(this,tr("Redimmensionner la photo"),tr("Width/Height"),QLineEdit::Normal,nullptr,&done);
  if (done)
  {
      QStringList values = input.split('/');
      resizeImage(values.at(0).toInt(),values.at(1).toInt());
  }
}
