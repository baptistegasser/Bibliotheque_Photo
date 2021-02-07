#include "imagefinder.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"
#include "iostream"

#include "db/db.h"
#include "model/image.h"

using namespace std;

ImageFinder::ImageFinder(QDir dir)
{
    this->rootDir = dir;
}

ImageFinder::ImageFinder(QString dirPath):
    ImageFinder(QDir(dirPath))
{
}

void ImageFinder::index() const
{
    QFileInfoList files = QFileInfoList();

    QQueue<QDir> queue = QQueue<QDir>();
    queue.enqueue(rootDir);

    QDir currentDir;
    QFileInfoList currentFilesInfos;
    QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks;
    while (!queue.empty()) {
        currentDir = queue.dequeue();
        currentFilesInfos = currentDir.entryInfoList(filters, QDir::DirsLast);
        for(const QFileInfo &fileInfo : qAsConst(currentFilesInfos)) {
            if (fileInfo.isDir()) {
                queue.enqueue(fileInfo.absoluteFilePath());
            } else {
                QImage q_img (fileInfo.absoluteFilePath());
                if (!q_img.isNull()) {
                    files.append(fileInfo);
                }
            }
        }
    }

    for (const QFileInfo &fic : files)
    {
        Image img(fic);
        DB::getImageDao().save(img);
    }
}

