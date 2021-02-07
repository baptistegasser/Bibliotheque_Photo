#ifndef QINPUTCUSTOM_H
#define QINPUTCUSTOM_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>

class QInputCustom : public QDialog
{
public:
    QInputCustom(QWidget *parent = nullptr, int num = 1, QList<QString> texts = {},QList<QString> preTexts = {});
    QStringList getStrings();

private:
    QList<QLineEdit*> fields;

};

#endif // QINPUTCUSTOM_H
