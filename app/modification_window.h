#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"
#include "QFileInfo"

class Modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT
private:
    QLabel _my_image;
    QFileInfo img;

public:
    explicit Modification_window(QWidget *parent = nullptr);
    void setImage(QImage image);
    void setImage(char* path);
    void setQFileInfo(QFileInfo img);
    void resizeImage(int w, int h);



public slots:
    void openResizeDialog();

};

#endif // MODIFICATION_WINDOW_H
