#ifndef PHOTOCARD_H
#define PHOTOCARD_H

#include <QWidget>

namespace Ui {
class photoCard;
}

class photoCard : public QWidget
{
    Q_OBJECT

public:
    explicit photoCard(QWidget *parent = nullptr);
    ~photoCard();

private:
    Ui::photoCard *ui;
};

#endif // PHOTOCARD_H
