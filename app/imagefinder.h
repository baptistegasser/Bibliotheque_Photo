#ifndef IMAGEFINDER_H
#define IMAGEFINDER_H

#include "QDir"
#include "QFileInfo"

class ImageFinder
{
private:
    QDir rootDir;

public:
    ImageFinder(QDir dir);
    ImageFinder(QString dirPath);
    void index() const;
};

#endif // IMAGEFINDER_H
