#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"
#include "QFileInfo"
#include "model/image.h"
#include "tagbutton.h"

class Modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT
private:
    Image img;
    QLabel _frame;
    QPixmap picture;
    QHBoxLayout * grid_layout_cat;
    QWidget * area_cat;

public:
    explicit Modification_window(QWidget *parent = nullptr, const Image *image = nullptr);
    void updateImage();
    void setQFileInfo(QFileInfo img);
    void resizeImage(int w, int h);
    void backToOriginal();
    void initDetail();
    TagButton* getTagButtonFromTag(Tag tag);




public slots:
    void openResizeDialog();
    void zoom();
    void comment();
    void addCategoryTag();

};

#endif // MODIFICATION_WINDOW_H
