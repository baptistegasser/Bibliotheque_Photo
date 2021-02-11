#include "dirindexer.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"
#include <QImageReader>
#include <QtConcurrent>

#include "db/db.h"
#include "model/image.h"

DirIndexer::DirIndexer(Directory dir, QObject *parent):
    QObject(parent),
    dirToIndex(dir)
{
    this->indexFilters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks;
    for (const QByteArray &b : QImageReader::supportedImageFormats()) {
        this->supportedFilesExtentions.append(QString(b));
    }
}

void DirIndexer::startIndexing()
{
    fileToIndex = -1;
    indexedFiles = 0;

    future = QtConcurrent::run(this, &DirIndexer::index);
}

QList<Directory> DirIndexer::index()
{
    findFilesToIndex();
    QList<Directory> result;
    indexDir(dirToIndex, &result);
    emit doneIndexing();
    return result;
}

void DirIndexer::findFilesToIndex()
{
    QQueue<QDir> queue = QQueue<QDir>();
    queue.enqueue(dirToIndex);

    while (!queue.isEmpty()) {
        QDir dir = queue.dequeue();
        QFileInfoList files = dir.entryInfoList(indexFilters, QDir::DirsFirst);
        for(const QFileInfo &fileInfo : qAsConst(files)) {
            if (fileInfo.isDir()) {
                queue.enqueue(QDir(fileInfo.absoluteFilePath()));
            } else {
                fileToIndex += 1;
            }
        }
    }

    emit fileToIndexChanged(fileToIndex);
}

void DirIndexer::indexDir(Directory &dir, QList<Directory> *indexedDirs)
{
    // Save dir
    DB::getDirectoryDao().save(dir);

    QQueue<Directory> subDirs = QQueue<Directory>();

    // Get all files/dirs in current dir and index them
    QFileInfoList filesInfos = dir.entryInfoList(indexFilters, QDir::DirsLast);
    for(const QFileInfo &fileInfo : qAsConst(filesInfos)) {
        if (fileInfo.isDir()) {
            Directory next(fileInfo.absoluteFilePath(), Directory::INCLUDE);
            subDirs.enqueue(next);
        } else {
            // Index only files with known valid extentions
            if (supportedFilesExtentions.contains(fileInfo.suffix())) {
                indexImage(dir, fileInfo);
            }

            this->indexedFiles += 1;
            emit indexedFilesChanged(indexedFiles);
        }
    }

    // Index all found directories
    indexedDirs->append(subDirs);
    for (Directory &currentDir : subDirs) {
        currentDir.parentDirPath = dir.absolutePath();
        indexDir(currentDir, indexedDirs);
    }
}

void DirIndexer::indexImage(const Directory &parent, const QFileInfo &infos)
{
    // Ignore if not an image
    QImage q_img (infos.absoluteFilePath());
    if (q_img.isNull()) {
        return;
    }

    Image img;
    img.path = infos.absoluteFilePath();
    img.parentDir = parent.absolutePath();
    img.name = infos.fileName();
    img.size = infos.size();
    img.width = q_img.width();
    img.height = q_img.height();

    // Only update the image color if new
    if (!DB::getImageDao().exist(img)) {
        img.main_color = img.get_mean_rgb();
    }

    DB::getImageDao().save(img);
}

QList<Directory> DirIndexer::getResult() const
{
    return future.result();
}
