#include "pinui.h"
#include "ui_pinui.h"

pinui::pinui(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pinui)
{
    ui->setupUi(this);
    connect(ui->pushButtonPIn,&QPushButton::clicked,this,&pinui::handlePinClick);

    connect(ui->num1,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num2,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num3,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num4,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num5,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num6,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num7,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num8,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num9,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->num0,&QPushButton::clicked,this,&pinui::handleClick);
    connect(ui->delete_2,&QPushButton::clicked,this,&pinui::handleClick);

    attTimer = new QTimer(this);

    connect(attTimer,&QTimer::timeout,this,&pinui::timeout);

}

pinui::~pinui()
{
    delete ui;
}

void pinui::showEvent(QShowEvent *event)
{

    QWidget::showEvent(event);
    time=10;
    attTimer->start(1000);
}

void pinui::handlePinClick()
{
    //qDebug()<<"handlepinclickissa";
    pin = ui->lineEditPin->text();
    ui->lineEditPin->setText("");

    emit pinSignal(pin);

    pin="";
    attTimer->stop();
}

void pinui::handleClick()
{
    QPushButton * button = qobject_cast<QPushButton*>(sender());
    QString name = button->objectName();

    if(name=="num1")
    {
        pin+="1";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num2")
    {
        pin+="2";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num3")
    {
        pin+="3";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num4")
    {
        pin+="4";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num5")
    {
        pin+="5";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num6")
    {
        pin+="6";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num7")
    {
        pin+="7";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num8")
    {
        pin+="8";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num9")
    {
        pin+="9";
        ui->lineEditPin->setText(pin);
    };
    if(name=="num0")
    {
        pin+="0";
        ui->lineEditPin->setText(pin);
    };
    if(name=="delete_2")
    {
        pin.removeLast();
        ui->lineEditPin->setText(pin);
    };
    time=10;
}

void pinui::timeout()
{
    qDebug()<<"toimii";
    if(time>=0)
    {
        time-=1;
    }
    if(time==0)
    {
        emit pinSignal("timeout");
        pin="";
        ui->lineEditPin->setText("");
        attTimer->stop();
    }
}
