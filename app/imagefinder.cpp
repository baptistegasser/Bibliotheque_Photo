#include "imagefinder.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"
#include "iostream"

/*ImageFinder::ImageFinder(const QDir rootDir)
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
}*/

ImageFinder::ImageFinder()
{
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::FileMode::DirectoryOnly);
    if(dialog.close())
    {
        this->rootDir.setPath(dialog.getExistingDirectory());
    }
}

QFileInfoList ImageFinder::getImagesList() const
{
    QFileInfoList files = QFileInfoList();

    QQueue<QDir> queue = QQueue<QDir>();
    queue.enqueue(rootDir);


    QDir currentDir;
    QList<QDir> visited;
    QFileInfoList currentFilesInfos;
    QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks;
    while (!queue.empty()) {
        currentDir = queue.dequeue();
        visited.append(currentDir);
        currentFilesInfos = currentDir.entryInfoList(filters, QDir::DirsLast);
        for(const QFileInfo &fileInfo : qAsConst(currentFilesInfos))
        {
            if (!visited.contains(fileInfo.absoluteDir()))
            {
                if (fileInfo.isDir()) {
                    queue.enqueue(fileInfo.absoluteDir());
                } else {
                    files.append(fileInfo);
                }
            }

        }
    }
    for(const QFileInfo &q : qAsConst(files))
    {
        std::cout << q.absolutePath().toStdString() << std::endl;
    }

    return files;



}

