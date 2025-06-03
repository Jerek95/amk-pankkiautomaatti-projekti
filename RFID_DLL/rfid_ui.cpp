#include "rfid_ui.h"
#include "ui_rfid_ui.h"

rfid_ui::rfid_ui(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::rfid_ui)
{
    ui->setupUi(this);
    port = new QSerialPort(this);
    connect(port,&QSerialPort::readyRead,this,&rfid_ui::handleReader);
    QPixmap pixmap(":/insertcard.png");
    ui->label->setPixmap(pixmap);
}

rfid_ui::~rfid_ui()
{
    delete ui;
}

bool rfid_ui::openPort()
{
    port->setPortName("");
    const auto serialPortInfos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &portInfo : serialPortInfos) {

        if (portInfo.serialNumber() == "OL56E09005B8EB6"){
                    port->setPortName(portInfo.portName());
        }
    }

    if (port->portName() == ""){
        qDebug() << "kortinlukijaa ei löydy";
        return false;
    }

    if (port->open(QIODeviceBase::ReadOnly)==false){
        qDebug() << "portti ei aukea";
        qDebug() << port->errorString();
        return false;
    }

    qDebug() << "portti on auki";

    return true;
}

void rfid_ui::closePort()
{
    port->close();
}

void rfid_ui::handleReader()
{

    QByteArray byteArray = port->readAll();
    QString str = QString::fromUtf8(byteArray);
    str.remove(0, 3).chop(3);
    emit sendSignalToEXE(str);
}
