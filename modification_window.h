#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"

class Modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT
private:
    QLabel _my_image;

public:
    explicit Modification_window(QWidget *parent = nullptr);
    void setImage(QImage image);
};

#endif // MODIFICATION_WINDOW_H
