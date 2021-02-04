#include "imagefinder.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"
#include "iostream"

#include "db/db.h"
#include "model/image.h"

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
        img.categoryTags.append(Tag("meme", "#ff0000"));
        img.feelingTags.append(Tag("fun", "#00ff00"));
        img.descriptiveTags.append(Tag("yes", "#0000ff"));
        DB::getImageDao().save(img);
        cout << fic.baseName().toStdString() << endl;
    }

    return files;
}

