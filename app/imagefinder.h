#ifndef IMAGEFINDER_H
#define IMAGEFINDER_H

#include "QDir"
#include "QFileInfo"

class ImageFinder
{
private:
    QDir rootDir;

public:
    ImageFinder();
    QFileInfoList getImagesList() const;
};

#endif // IMAGEFINDER_H
