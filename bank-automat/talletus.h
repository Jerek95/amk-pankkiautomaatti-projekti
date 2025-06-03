#ifndef TALLETUS_H
#define TALLETUS_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class talletus;
}

class talletus : public QDialog
{
    Q_OBJECT

public:
    explicit talletus(QWidget *parent = nullptr);
    ~talletus();
    void handlesendButton();

signals:
    void sendTalletusSum(QString);

private:
    Ui::talletus *ui;
};

#endif // TALLETUS_H
