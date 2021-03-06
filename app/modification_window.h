#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"
#include "QFileInfo"
#include "model/image.h"
#include "tagbutton.h"
#include "flowlayout.h"
#include "QDialogButtonBox"

class Modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT
private:
    Image *img;
    QLabel _frame;
    QPixmap picture;
    FlowLayout * grid_layout_cat;
    QWidget * area_cat;
    FlowLayout * grid_layout_feel;
    QWidget * area_feel;
    FlowLayout * grid_layout_desc;
    QWidget * area_desc;
    QList<QPushButton*> stars;
    QPushButton * croppAccept;
    QPushButton * croppCancel;
    bool ratio;

public:
    explicit Modification_window(QWidget *parent = nullptr, Image *image = nullptr);
    void updateImage();
    void setQFileInfo(QFileInfo img);
    void resizeImage(int w, int h);
    void backToOriginal();
    void initLayout();
    void initTopLayout();
    void initDetail();
    TagButton* getTagButtonFromTag(Tag tag);
    QPushButton* getReturnButton();
    void initAlbum();





public slots:
    void openResizeDialog();
    void zoom();
    void comment();
    void addTag(int i);
    void changeNote(int i);
    void save();
    void cropped();
    void toCrop(QRect rect);
    void cropCancel();
    void selectAlbum();

};

#endif // MODIFICATION_WINDOW_H
