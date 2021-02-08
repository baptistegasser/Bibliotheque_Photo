#include "dirindexer.h"
#include "QMutableListIterator"
#include "QQueue"
#include "QFileDialog"

#include "db/db.h"
#include "model/image.h"

DirIndexer::DirIndexer(Directory dir):
    dirToIndex(dir)
{
    this->indexFilters = QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Readable | QDir::NoSymLinks;
}

QList<Directory> DirIndexer::index()
{
    QList<Directory> indexedDirs;
    indexDir(dirToIndex, &indexedDirs);
    return indexedDirs;
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
            indexImage(dir, fileInfo);
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
        //img.main_color = img.get_mean_rgb();
    }

    DB::getImageDao().save(img);
}
