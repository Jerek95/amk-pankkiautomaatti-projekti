#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_retrievalButton_clicked()
{

    QString site_url="http://localhost:3000/asiakas";
    QNetworkRequest request(site_url);
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::getAsiakasSlot);

    reply = manager->get(request);
}

void MainWindow::getAsiakasSlot (QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString asiakas;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        asiakas+=QString::number(json_obj["puhelinnumero"].toInt())+", "+json_obj["etunimi"].toString()+", "+json_obj["sukunimi"].toString()+", "+json_obj["osoite"].toString()+", "+json_obj["tunnus"].toString()+"\r";
    }

    ui->asiakasInfo->setText(asiakas);

    reply->deleteLater();
    manager->deleteLater();
}

void MainWindow::on_tilitapButton_clicked()
{
    QString site_url="http://localhost:3000/tilitapahtumat";
    QNetworkRequest request(site_url);
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::getTilitapSlot);

    reply = manager->get(request);
}

void MainWindow::getTilitapSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    QString asiakas;
    foreach (const QJsonValue &value, json_array) {
        QJsonObject json_obj = value.toObject();
        asiakas+=QString::number(json_obj["kortinnumero"].toInt())+", "+json_obj["tilinumero"].toString()+", "+json_obj["paivamaara"].toString()+", "+json_obj["tapahtuma"].toString()+", "+QString::number(json_obj["summa"].toInt())+"\r";
    }

    ui->tilitapInfo->setText(asiakas);

    reply->deleteLater();
    manager->deleteLater();
}

void MainWindow::on_tilitapPostButton_clicked()
{
     qDebug()<<"toimii";
    QJsonObject jsonObj;
    jsonObj.insert("tilinumero",ui->tilinumero->text());
    jsonObj.insert("kortinnumero",ui->kortinnumero->text().toInt());
    jsonObj.insert("paivamaara",ui->paivamaara->text());
    jsonObj.insert("tapahtuma",ui->tapahtuma->text());
    jsonObj.insert("summa",ui->summa->text().toInt());

    QString site_url="http://localhost:3000/tilitapahtumat";
    QNetworkRequest request(site_url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::addTilitapSlot);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void MainWindow::addTilitapSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    manager->deleteLater();
}

