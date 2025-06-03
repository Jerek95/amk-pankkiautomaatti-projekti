#ifndef RFID_UI_H
#define RFID_UI_H

#include "RFID_DLL_global.h"
#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QPixmap>

namespace Ui {
class rfid_ui;
}

class RFID_DLL_EXPORT rfid_ui : public QDialog
{
    Q_OBJECT

public:
    explicit rfid_ui(QWidget *parent = nullptr);
    ~rfid_ui();
    bool openPort();
    void closePort();

signals:
    void sendSignalToEXE(QString);

private slots:
    void handleReader();

private:
    Ui::rfid_ui *ui;
    QSerialPort* port;
};

#endif // RFID_UI_H
