#ifndef PINUI_H
#define PINUI_H

#include <QDialog>
#include <QDebug>
#include "pinUI_DLL_global.h"
#include <QString>
#include <QTimer>
#include <QShowEvent>
#include <QWidget>

namespace Ui {
class pinui;
}

class PINUI_DLL_EXPORT pinui : public QDialog
{
    Q_OBJECT

public:
    explicit pinui(QWidget *parent = nullptr);
    ~pinui();

private:
    Ui::pinui *ui;
    QString pin;
    QTimer * attTimer;
    int time=10;

    void showEvent(QShowEvent *event);

private slots:
    void handlePinClick();
    void handleClick();
    void timeout();

signals:
    void pinSignal(QString);
};

#endif // PINUI_H
