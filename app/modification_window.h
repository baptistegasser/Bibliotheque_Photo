#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"
#include "QFileInfo"
#include "model/image.h"

class Modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT
private:
    Image img;
    QLabel _frame;
    QPixmap picture;

public:
    explicit Modification_window(QWidget *parent = nullptr, const Image *image = nullptr);
    void updateImage();
    void setQFileInfo(QFileInfo img);
    void resizeImage(int w, int h);
    void backToOriginal();




public slots:
    void openResizeDialog();
    void zoom();
    void comment();
};

#endif // MODIFICATION_WINDOW_H
