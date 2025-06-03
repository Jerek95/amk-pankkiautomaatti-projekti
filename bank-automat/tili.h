#ifndef TILI_H
#define TILI_H

#include <QDialog>

namespace Ui {
class tili;
}

class tili : public QDialog
{
    Q_OBJECT

public:
    explicit tili(QWidget *parent = nullptr);
    ~tili();
     Ui::tili *ui;
};

#endif // TILI_H
