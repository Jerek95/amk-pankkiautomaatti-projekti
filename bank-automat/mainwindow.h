#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "pankki.h"
#include "rfid_ui.h"
#include "pinui.h"
#include <QTimer>
#include "asiakas.h"
#include "kortti.h"
#include "restapi_dll.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int state=0;
    int attempts=3;
    int time=10;

private slots:
    void handleCardButton();
    void on_kirjaudu_pressed();
    void handleRFIDsignal(QString);
    void handlePinSignal(QString);
    void handleRestPinSignal(bool);
    void timeout();
    void handleToken(QByteArray);
    void handleId(QString, QString, QString, QString,QString);
    void handleKirjauduUlos();
    void handleErrorSignal(QString);

signals:
    void sendToken(QByteArray);
    void errorSignal(QString);

private:
    Ui::MainWindow *ui;
    pankki * ptrPankki;
    rfid_ui * ptrDLLui;
    pinui * ptrUi;
    QString pin;
    QString cardNum;
    QTimer * attTimer;
    Restapi_DLL* rest;
    QByteArray token;
    bool compare;
    QString tunnus;
    QString kortinnumero; QString tilinumero; QString nimi;
    QString kortinlukija;
};
#endif // MAINWINDOW_H
