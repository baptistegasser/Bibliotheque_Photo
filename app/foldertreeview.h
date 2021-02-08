#ifndef FOLDERTREEVIEW_H
#define FOLDERTREEVIEW_H

#include "model/directory.h"
#include "model/image.h"
#include <QTreeWidget>

class FolderTreeView : public QTreeWidget
{
    Q_OBJECT

public:
    FolderTreeView(QWidget *parent = nullptr);
    void displayDir(const Directory &dir);
    void displayDirs(const QList<Directory> &dirs);

private:
    QTreeWidgetItem *test(Directory &dir);
    void displayImages(const QList<Image> &images, QTreeWidgetItem *parent);

protected slots:
    void onItemExpanded(QTreeWidgetItem *item);
    void onItemCollapsed(QTreeWidgetItem *item);
};

#endif // FOLDERTREEVIEW_H
