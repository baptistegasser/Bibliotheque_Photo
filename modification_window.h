#ifndef MODIFICATION_WINDOW_H
#define MODIFICATION_WINDOW_H

#include "ui_modification_window.h"

class modification_window : public QWidget, private Ui::modification_window
{
    Q_OBJECT

public:
    explicit modification_window(QWidget *parent = nullptr);
};

#endif // MODIFICATION_WINDOW_H
