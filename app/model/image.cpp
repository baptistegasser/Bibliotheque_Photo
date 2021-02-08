#include "image.h"

#include <QImage>
#include <iostream>

Image::Image()
{
    path = "";
    parentDir = "";
    name = "";
    size = 0;
    width = 0;
    height = 0;
    rating = 0;
    comment = "";
    resized = false;
    res_width = 0;
    res_height = 0;
    cropped = false;
    crop_x = 0;
    crop_y = 0;
    crop_width = 0;
    crop_height = 0;
    main_color = QVector<int>(3);
}

Image::Image(const Image &img)
{
    *this = img;
}

Image &Image::operator =(const Image &img)
{
    if (this == &img) {
        return *this;
    }

    path = img.path;
    parentDir = img.parentDir;
    name = img.name;
    size = img.size;
    width = img.width;
    height = img.height;
    rating = img.rating;
    comment = img.comment;
    resized = img.resized;
    res_width = img.res_width;
    res_height = img.res_height;
    cropped = img.cropped;
    crop_x = img.crop_x;
    crop_y = img.crop_y;
    crop_width = img.crop_width;
    crop_height = img.crop_height;
    main_color = img.main_color;

    return *this;
}

bool Image::equal(const Image& img) const
{
    return path == img.path &&
            name == img.name &&
            size == img.size &&
            width == img.width &&
            height == img.height &&
            rating == img.rating &&
            comment == img.comment &&
            feelingTags == img.feelingTags &&
            descriptiveTags == img.descriptiveTags &&
            categoryTags == img.categoryTags;
}

bool Image::operator== (const Image& img) const
{
    return path == img.path;
}

bool Image::operator!= (const Image& img) const
{
    return !(*this == img);
}

Image::operator QString() const
{
    QString s("{\n\tpath: %path%\n\tname: %name%\n\tsize: %size%, width: %width%, height: %height%, rating: %rating%\n\tcomment: %comment%\n\tfeelingTags: { %feelingTags% }\n\tdescriptiveTags: { %descriptiveTags% }\n\tcategoryTags: { %categoryTags% }\n}");

    s.replace("\t", "    ");
    s.replace("%path%", path);
    s.replace("%name%", name);
    s.replace("%size%", QString::number(size));
    s.replace("%width%", QString::number(width));
    s.replace("%height%", QString::number(height));
    s.replace("%rating%", QString::number(rating));
    s.replace("%comment%", comment);
    s.replace("%feelingTags%", Tag::listToQString(feelingTags));
    s.replace("%descriptiveTags%", Tag::listToQString(descriptiveTags));
    s.replace("%categoryTags%", Tag::listToQString(categoryTags));

    return s;
}
//  Source : https://stackoverflow.com/a/61581999
QVector<int> Image::get_mean_rgb(){
    QImage img(path);
    if (img.isNull()) {
        qCritical("The given file is not a valid image");
    }

    QRgb *ct;
    int width , height;
    width = img.width();
    height = img.height();

    QVector<int> red(256);
    QVector<int> green(256);
    QVector<int> blue(256);
    for(int i = 0 ; i < height ; i++){
        ct = (QRgb *)img.scanLine(i);
        for(int j = 0 ; j < width ; j++){
            red[qRed(ct[j])]+=1;
            green[qGreen(ct[j])]+=1;
            blue[qBlue(ct[j])]+=1;
        }
    }

    int red_val = get_max(red);
    int green_val = get_max(green);
    int blue_val = get_max(blue);

    QVector<int> result(3);
    result.insert(0 , red_val);
    result.insert(1 , green_val);
    result.insert(2 , blue_val);

    return result;
}
int Image::get_max(QVector<int> vec){
    int max = vec[0];
    int index = 0;
    for(int i = 0 ; i < 255 ; i++){
        if(vec[i] > max){
            max = vec[i];
            index = i;
        }
    }
    return index;
}
