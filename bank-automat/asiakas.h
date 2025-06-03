#ifndef ASIAKAS_H
#define ASIAKAS_H

#include <QDialog>

namespace Ui {
class Asiakas;
}

class Asiakas : public QDialog
{
    Q_OBJECT

public:
    explicit Asiakas(QWidget *parent = nullptr);
    ~Asiakas();
    Ui::Asiakas *ui;
};

#endif // ASIAKAS_H
