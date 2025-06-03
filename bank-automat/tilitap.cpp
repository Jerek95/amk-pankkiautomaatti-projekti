#include "tilitap.h"
#include "ui_tilitap.h"

tilitap::tilitap(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tilitap)
{
    ui->setupUi(this);
    clicks=0;
    connect(ui->nextButton,&QPushButton::clicked,this,&tilitap::handleNext);
    connect(ui->previousButton,&QPushButton::clicked,this,&tilitap::handleprevious);
}

tilitap::~tilitap()
{
    delete ui;
}

void tilitap::setJsonArray(QJsonArray json_ar)
{
    QList<QJsonValue> list;
    for (const QJsonValue &val : json_ar) {
        list.append(val);
    }

    std::reverse(list.begin(), list.end());

    json_array = QJsonArray();
    for (const QJsonValue &val : list) {
        json_array.append(val);
    }

    //qDebug()<<"array : "<<json_ar;
    QJsonObject json_obj = json_array[0].toObject();

    qDebug() << "JSON Object: " << json_obj;

    tilinumero = json_obj["tilinumero"].toString();
    kortinnumero=json_obj["kortinnumero"].toString();
    paivamaara=json_obj["paivamaara"].toString();
    tapahtuma=json_obj["tapahtuma"].toString();
    summa = json_obj["summa"].toString();

}

void tilitap::setLineEdits()
{
    ui->tilinumero->setText(tilinumero);
    ui->kortinnumero->setText(kortinnumero);
    ui->paivamaara->setText(paivamaara);
    ui->tapahtuma->setText(tapahtuma);
    ui->summa->setText(summa);
    show();
}

void tilitap::handleNext()
{
    clicks+=1;

    if(clicks!=10)
    {
    if (clicks < json_array.size()) {
        QJsonObject json_obj = json_array[clicks].toObject();
        tilinumero = json_obj["tilinumero"].toString();
        kortinnumero=json_obj["kortinnumero"].toString();
        paivamaara=json_obj["paivamaara"].toString();
        tapahtuma=json_obj["tapahtuma"].toString();
        summa = json_obj["summa"].toString();


    } else {
        qDebug() << "No more items in array";
        clicks = json_array.size() - 1;
    }

    ui->tilinumero->setText(tilinumero);
    ui->kortinnumero->setText(kortinnumero);
    ui->paivamaara->setText(paivamaara);
    ui->tapahtuma->setText(tapahtuma);
    ui->summa->setText(summa);
    }
    else
    {
        qDebug() << "reached max";
        clicks-=1;
    }
}

void tilitap::handleprevious()
{
    if(clicks!=0)
    {
    clicks-=1;
    }

    QJsonObject json_obj = json_array[clicks].toObject();

    tilinumero = json_obj["tilinumero"].toString();
    kortinnumero=json_obj["kortinnumero"].toString();
    paivamaara=json_obj["paivamaara"].toString();
    tapahtuma=json_obj["tapahtuma"].toString();
    summa = json_obj["summa"].toString();


    ui->tilinumero->setText(tilinumero);
    ui->kortinnumero->setText(kortinnumero);
    ui->paivamaara->setText(paivamaara);
    ui->tapahtuma->setText(tapahtuma);
    ui->summa->setText(summa);
}
