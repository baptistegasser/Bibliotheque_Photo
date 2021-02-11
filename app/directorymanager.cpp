#include "directorymanager.h"

#include "db/db.h"
#include "dirindexer.h"

#include <QFileDialog>
#include <QStack>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTreeWidget>

DirectoryManager::DirectoryManager(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    // Configure buttons
    _del_dir_btn->setEnabled(false);
    connect(_add_dir_btn, &QPushButton::clicked, this, &DirectoryManager::addDirectory);
    connect(_add_first_btn, &QPushButton::clicked, this, &DirectoryManager::addDirectory);
    connect(_del_dir_btn, &QPushButton::clicked, this, &DirectoryManager::removeDirectory);

    // Configure folder tree
    _dir_tree->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    connect(_dir_tree, &QTreeWidget::itemExpanded, this, &DirectoryManager::onItemExpanded);
    connect(_dir_tree, &QTreeWidget::itemCollapsed, this, &DirectoryManager::onItemCollapsed);
    connect(_dir_tree, &QTreeWidget::itemSelectionChanged, this, &DirectoryManager::onItemSelected);

    // Detect if no folder was added
    QList<Directory> dirs = DB::getDirectoryDao().getAll();
    if (dirs.isEmpty()) {
        _stackpane->setCurrentIndex(2);
    } else {
        displayDirs(dirs);
    }
}

void DirectoryManager::addDirectory()
{
    QString dirPath = getDirectoryDialog();
    if (dirPath.isNull()) {
        return;
    }

    // Show progress
    _stackpane->setCurrentIndex(1);

    Directory directory(dirPath, Directory::INCLUDE);
    DirIndexer *indexer = new DirIndexer(directory);
    connect(indexer, &DirIndexer::fileToIndexChanged, this,  [=](int i) {
        _progress->setMaximum(i);
        _progress->setFormat("%p% fichier traité sur " + QString::number(i));
    });
    connect(indexer, &DirIndexer::indexedFilesChanged, this, [=](int i) { _progress->setValue(i); });
    connect(indexer, &DirIndexer::doneIndexing, this, [=]() {
        displayDir(directory, true);
        displayDirs(indexer->getResult());
        _stackpane->setCurrentIndex(0);
        emit directoryAdded();
    });

    indexer->startIndexing();
}

QString DirectoryManager::getDirectoryDialog()
{
    QString caption = "Ouvrir un dossier";
    // Try to get a standard folder
    QString dir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (dir.isEmpty()) {
        dir = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    }

    QFileDialog dialog(this, caption, dir);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setOptions(QFileDialog::DontResolveSymlinks);

    if (dialog.exec() == QDialog::Rejected) {
        return QString::Null();
    }

    if (!dialog.selectedFiles().isEmpty()) {
        return dialog.selectedFiles()[0];
    }
    return dialog.directory().absolutePath();
}

void DirectoryManager::displayDirs(const QList<Directory> &dirs)
{
    for (const Directory &dir : dirs) {
        displayDir(dir, false);
    }
}

void DirectoryManager::displayDir(const Directory &dir, bool expanded)
{
    Directory tmp(dir);
    QTreeWidgetItem *item = createDirItem(tmp);
    item->setData(0, Qt::UserRole, QVariant(true));
    item->setData(1, Qt::UserRole, dir.absolutePath());
    if (expanded) {
        expandItem(item);
    }

    displayImages(DB::getImageDao().getInDir(dir), item);
}

QTreeWidgetItem *DirectoryManager::createDirItem(Directory &dir)
{
    QTreeWidgetItem *dirItem = nullptr;
    QString dirName = dir.dirName();
    if (dirName.isEmpty()) {
        dirName = "/";
    }

    if (dir.cdUp()) {
        QTreeWidgetItem *parent = createDirItem(dir);
        for (int i = 0; i < parent->childCount(); ++i) {
            if (parent->child(i)->text(0) == dirName) {
                dirItem = parent->child(i);
                break;
            }
        }

        if (dirItem == nullptr) {
            dirItem = new QTreeWidgetItem(parent);
            parent->insertChild(0, dirItem);
        }
    } else {
        for (int i = 0; i < _dir_tree->topLevelItemCount(); ++i) {
            if (_dir_tree->topLevelItem(i)->text(0) == dirName) {
                dirItem = _dir_tree->topLevelItem(i);
                break;
            }
        }

        if (dirItem == nullptr) {
            dirItem = new QTreeWidgetItem();
            _dir_tree->addTopLevelItem(dirItem);
        }
    }

    dirItem->setText(0, dirName);
    dirItem->setIcon(0, QIcon(":/icon/folder_closed"));
    return dirItem;
}

void DirectoryManager::displayImages(const QList<Image> &images, QTreeWidgetItem *parent)
{
    // Yeet the childs
    foreach(auto child, parent->takeChildren()) delete child;

    for (const Image &img : images) {
        QTreeWidgetItem *item = new QTreeWidgetItem(parent);
        item->setIcon(0, QIcon(":/icon/image_frame"));
        item->setText(0, img.name);
        parent->addChild(item);
    }
}

void DirectoryManager::expandItem(QTreeWidgetItem *item)
{
    QStack<QTreeWidgetItem *> items;
    items.push(item);

    QTreeWidgetItem *current = item;
    while (current->parent() != nullptr) {
        current = current->parent();
        items.push(current);
    }

    while (!items.isEmpty()) {
        items.pop()->setExpanded(true);
    }
}

void DirectoryManager::removeDirectory()
{
    _dir_tree->setDisabled(true);

    if (_dir_tree->selectedItems().size() != 1) {
        qInfo() << __FUNCTION__ << "more than one item selected to remove";
        _dir_tree->setDisabled(false);
        return;
    }

    QTreeWidgetItem *item = _dir_tree->selectedItems().at(0);
    QString dirPath = item->data(1, Qt::UserRole).toString();

    Directory dir = DB::getDirectoryDao().getByPath(dirPath);
    if (dir == Directory::INVALID) {
        _dir_tree->setDisabled(false);
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Condirmation", "Supprimer le dossier "+dir.absolutePath()+" ?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        DB::getDirectoryDao().remove(dir);
        removeDir(dir);
        emit directoryRemoved();
    }

    _dir_tree->setDisabled(false);

    // Check that we style have indexed dirs
    if (_dir_tree->topLevelItemCount() == 0 && DB::getDirectoryDao().getAll().size() == 0) {
        _stackpane->setCurrentIndex(2);
    }
}

void DirectoryManager::removeDir(Directory &dir)
{
    QList<QString> aaah;
    do {
        QString name = dir.dirName();
        if (name.isEmpty()) name = "/";
        aaah.insert(0, name);
    } while (dir.cdUp());

    // Get top level item
    QTreeWidgetItem *parent = nullptr;
    for (int i = 0; i < _dir_tree->topLevelItemCount(); i += 1) {
        if (_dir_tree->topLevelItem(i)->text(0) == aaah[0]) {
            parent = _dir_tree->topLevelItem(i);
            break;
        }
    }
    if (parent == nullptr) {
        return;
    }

    // Go down to the item matching the dir
    QTreeWidgetItem *dirItem = parent;
    for (int i = 1; i < aaah.size(); ++i) {
        for (int j = 0; j < dirItem->childCount(); ++j) {
            if (dirItem->child(j)->text(0) == aaah[i]) {
                dirItem = dirItem->child(j);
                break;
            }
        }
    }

    // Go back up until we should not delete
    QTreeWidgetItem *upItem;
    while (true) {
        upItem = dirItem->parent();

        // Quit if at top or parent folder contain other items
        if (upItem == nullptr || upItem->childCount() > 1) {
            break;
        }

        dirItem = upItem;
    }

    delete dirItem;
}

bool DirectoryManager::isDirItem(const QTreeWidgetItem *item)
{
    QVariant data = item->data(0, Qt::UserRole);
    return data.canConvert(QVariant::Bool) && data.toBool();
}

void DirectoryManager::onItemSelected()
{
    bool enabled = false;

    // If only one item selected, check if it contain data that mark it as a dir
    if (_dir_tree->selectedItems().size() == 1) {
        QVariant isDir = _dir_tree->selectedItems().at(0)->data(0, Qt::UserRole);
        if (isDir.isValid() && isDir.toBool()) {
            enabled = true;
        }
    }

    _del_dir_btn->setEnabled(enabled);
}

void DirectoryManager::onItemExpanded(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":/icon/folder_open"));
}

void DirectoryManager::onItemCollapsed(QTreeWidgetItem *item)
{
    item->setIcon(0, QIcon(":/icon/folder_closed"));
}
