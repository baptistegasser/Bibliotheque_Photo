#include "imagefinder.h"
#include "QMutableListIterator"
#include "QQueue"

ImageFinder::ImageFinder(const QDir rootDir)
{
    this->rootDir = rootDir;
}

QFileInfoList ImageFinder::getImagesList() const
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

        QFileInfo fileInfo;
        QMutableListIterator<QFileInfo> it (currentFilesInfos);
        while (it.hasNext()) {
            fileInfo = it.next();

            if (fileInfo.isDir()) {
                queue.enqueue(fileInfo.absoluteDir());
            } else {
                files.append(fileInfo);
            }
        }
    }

    return files;
}
