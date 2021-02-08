#include "foldertreeview.h"

#include "db/db.h"
#include <QCollator>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMimeData>
#include <QStack>

FolderTreeView::FolderTreeView(QWidget *parent) :
    QTreeWidget(parent)
{
    this->setAcceptDrops(true);
    this->viewport()->setAcceptDrops(true);
    this->setDropIndicatorShown(true);
    connect(this, &FolderTreeView::itemExpanded, this, &FolderTreeView::onItemExpanded);
    connect(this, &FolderTreeView::itemCollapsed, this, &FolderTreeView::onItemCollapsed);
}

void FolderTreeView::displayDir(const Directory &dir)
{
    Directory tmp(dir);
    QTreeWidgetItem *item = test(tmp);
    displayImages(DB::getImageDao().getInDir(dir), item);
}

QTreeWidgetItem *FolderTreeView::test(Directory &dir)
{
    QTreeWidgetItem *dirItem = nullptr;
    QString dirName = dir.dirName();
    if (dirName.isEmpty()) {
        dirName = "/";
    }

    if (dir.cdUp()) {
        QTreeWidgetItem *parent = test(dir);
        for (int i = 0; i < parent->childCount(); ++i) {
            if (parent->child(i)->text(0) == dirName) {
                dirItem = parent->child(i);
                break;
            }
        }

        if (dirItem == nullptr) {
            dirItem = new QTreeWidgetItem(parent);
            parent->addChild(dirItem);
        }
    } else {
        for (int i = 0; i < topLevelItemCount(); ++i) {
            if (topLevelItem(i)->text(0) == dirName) {
                dirItem = topLevelItem(i);
                break;
            }
        }

        if (dirItem == nullptr) {
            dirItem = new QTreeWidgetItem();
            addTopLevelItem(dirItem);
        }
    }

    dirItem->setText(0, dirName);
    dirItem->setIcon(0, QIcon(":/icon/folder_closed"));
    return dirItem;
}

void FolderTreeView::displayDirs(const QList<Directory> &dirs)
{
    for (const Directory &dir : dirs) {
        displayDir(dir);
    }
}

void FolderTreeView::displayImages(const QList<Image> &images, QTreeWidgetItem *parent)
{
    for (const Image &img : images) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setIcon(0, QIcon(":/icon/image_frame"));
        item->setText(0, img.name);
        parent->addChild(item);
    }
}

void FolderTreeView::onItemExpanded(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":/icon/folder_open"));
}

void FolderTreeView::onItemCollapsed(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":/icon/folder_closed"));
}
