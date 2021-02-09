#ifndef DIRECTORYMANAGER_H
#define DIRECTORYMANAGER_H

#include "ui_directorymanager.h"
#include "model/directory.h"
#include "model/image.h"

class DirectoryManager : public QWidget, private Ui::DirectoryManager
{
    Q_OBJECT

public:
    explicit DirectoryManager(QWidget *parent = nullptr);

private:
    QString getDirectoryDialog();
    void displayDirs(const QList<Directory> &dirs);
    void displayDir(const Directory &dir, bool extanded);
    void removeDirs(const QList<Directory> &dirs);
    void removeDir(Directory &dir);
    QTreeWidgetItem *createDirItem(Directory &dir);
    void displayImages(const QList<Image> &images, QTreeWidgetItem *parent);
    void expandItem(QTreeWidgetItem *item);
    bool isDirItem(const QTreeWidgetItem *item);

private slots:
    void addDirectory();
    void addFirstDirectory();
    void removeDirectory();
    void onItemSelected();
    void onItemExpanded(QTreeWidgetItem *item);
    void onItemCollapsed(QTreeWidgetItem *item);

signals:
    void directoryAdded();
    void directoryRemoved();
};

#endif // DIRECTORYMANAGER_H
