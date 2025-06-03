#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{   
    ui->setupUi(this);

    for (auto child : ui->centralwidget->findChildren<QWidget*>()) {
        child->setVisible(false);  // Hide all children of the central widget
    }

    this->showMaximized();

    connect(ui->card,&QPushButton::clicked, this,&MainWindow::handleCardButton);

    state=0;
    ptrDLLui = new rfid_ui(this);
    ptrUi = new pinui(this);

    connect(ptrDLLui,&rfid_ui::sendSignalToEXE, this,&MainWindow::handleRFIDsignal);
    connect(ptrUi,&pinui::pinSignal,this,&MainWindow::handlePinSignal);

    attTimer = new QTimer(this);
    connect(attTimer,&QTimer::timeout,this,&MainWindow::timeout);
    ui->attLine->setText(QString::number(attempts));

    rest = new Restapi_DLL(this);
    connect(rest, &Restapi_DLL::compareResult, this, &MainWindow::handleRestPinSignal);
    connect(rest, &Restapi_DLL::sendToken, this, &MainWindow::handleToken);
    connect(rest, &Restapi_DLL::sendId, this, &MainWindow::handleId);
    connect(this, &MainWindow::errorSignal,this,&MainWindow::handleErrorSignal);

    cardNum=0;
    ptrDLLui->openPort();
    ptrDLLui->show();

    qDebug()<<"Card Button pressed";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleCardButton()
{

    if(state==0)
    {
    cardNum=0;
    ptrDLLui->openPort();
    ptrDLLui->show();
    qDebug()<<"Card Button pressed";
    }
}

void MainWindow::on_kirjaudu_pressed()
{
    rest->onLogin(cardNum,pin);
}

void MainWindow::handleRFIDsignal(QString s)
{
    qDebug()<<"Signaali vastaanotettu";
    cardNum = s;
    ui->cardNum->setText(s);
    ptrDLLui->close();
    ptrUi->show();
    ptrDLLui->closePort();
}

void MainWindow::handlePinSignal(QString s)
{
    if(s=="timeout")
    {
        ptrUi->close();
        cardNum=0;
        ptrDLLui->openPort();
        ptrDLLui->show();
    }else
    {
    pin = s;
    ui->pinNum->setText(pin);
    ptrUi->close();
    rest->onLogin(cardNum,pin);
    }
}

void MainWindow::handleRestPinSignal(bool comparision)
{
    compare=comparision;

    if(comparision==true &&kortinlukija!="lukittu")
    {
        ptrPankki = new pankki(this);
        connect(ptrPankki,&pankki::kirjauduUlosSignal,this,&MainWindow::handleKirjauduUlos);
        pin=0;
        cardNum=0;
        ui->cardNum->setText("");
        ui->pinNum->setText("");
        attempts=3;
        state=0;
        ptrPankki->setToken(token);
        ptrPankki->setId(tunnus,kortinnumero,tilinumero,nimi);
    }
    if(comparision==false)
    {
        qDebug()<<"pin wrong";
        emit errorSignal("Pin väärin. Yrityksiä jäljellä: "+QString::number(attempts));
        attempts-=1;
        if(attempts>0) ptrUi->show();
    }else if(kortinlukija=="lukittu")
    {
        emit errorSignal("Korttisi on lukittu");

        cardNum=0;
        ptrDLLui->openPort();
        ptrDLLui->show();
    }

    if(attempts==0)
    {
        qDebug()<<"Attempts loppu";
        //state=1;
        //time=10;
        //attTimer->start(1000);
        emit errorSignal("Liian monta yritystä. Kortti lukitaan.");
        rest->lockCard();

        attempts=3;
        cardNum=0;
        ptrDLLui->openPort();
        ptrDLLui->show();
    }

    ui->attLine->setText(QString::number(attempts));
}

void MainWindow::timeout()
{
    time -=1;
    ui->timerLine->setText(QString::number(time));

    if(time<=0)
    {
        attTimer->stop();
        attempts=3;
        ui->attLine->setText(QString::number(attempts));
        state=0;
    }
}

void MainWindow::handleToken(QByteArray tokenr)
{
    token =tokenr;
}

void MainWindow::handleId(QString tunnusr, QString kortinnumeror, QString tilinumeror, QString nimir,QString kortinlukijar)
{
    kortinlukija =kortinlukijar;
    tunnus = tunnusr;
    kortinnumero=kortinnumeror;
    tilinumero=tilinumeror;
    nimi = nimir;
    qDebug()<<kortinlukija;
}

void MainWindow::handleKirjauduUlos()
{
    qDebug()<<"kirjauduit ulos";
    pin=0;
    cardNum=0;
    ui->cardNum->setText("");
    ui->pinNum->setText("");
    attempts=3;
    state=0;
    ptrDLLui->openPort();
    ptrDLLui->show();
}

void MainWindow::handleErrorSignal(QString error)
{
    QMessageBox objMessageBox;
    objMessageBox.setText(error);
    objMessageBox.exec();
}
