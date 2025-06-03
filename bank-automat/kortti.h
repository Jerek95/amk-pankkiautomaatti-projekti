#ifndef KORTTI_H
#define KORTTI_H

#include <QDialog>

namespace Ui {
class kortti;
}

class kortti : public QDialog
{
    Q_OBJECT

public:
    explicit kortti(QWidget *parent = nullptr);
    ~kortti();
    Ui::kortti *ui;
};

#endif // KORTTI_H
