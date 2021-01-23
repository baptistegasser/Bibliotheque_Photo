#ifndef IMAGEDIR_H
#define IMAGEDIR_H

#include "QString"

class ImageDir
{
public:
    const int ID;
    const QString path;

    ImageDir(int ID, QString path);
};

#endif // IMAGEDIR_H
