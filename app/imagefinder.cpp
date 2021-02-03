#include "imagefinder.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"
#include "iostream"

using namespace std;


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
    QFileInfoList currentFilesInfos;
    QDir::Filters filters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks;
    while (!queue.empty()) {
        currentDir = queue.dequeue();
        currentFilesInfos = currentDir.entryInfoList(filters, QDir::DirsLast);
        for(const QFileInfo &fileInfo : qAsConst(currentFilesInfos))
        {
                if (fileInfo.isDir()) {
                    queue.enqueue(fileInfo.absoluteFilePath());
                } else {
                    files.append(fileInfo);
                }
            }
        }

    for (QFileInfo fic : files)
    {
        cout << fic.baseName().toStdString() << endl;
    }
    return files;



}

