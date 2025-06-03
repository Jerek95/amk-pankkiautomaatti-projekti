#ifndef NOSTO_H
#define NOSTO_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class nosto;
}

class nosto : public QDialog
{
    Q_OBJECT

public:
    explicit nosto(QWidget *parent = nullptr);
    ~nosto();
    void handleNostoButton();

signals:
    void sendNostoSignal(QString);

private:
    Ui::nosto *ui;
};

#endif // NOSTO_H
