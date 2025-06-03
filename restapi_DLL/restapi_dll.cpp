#include "restapi_dll.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDebug>


Restapi_DLL::Restapi_DLL(QObject * parent) : QObject(parent)
{

}

void Restapi_DLL::getAsiakasSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString tunnus = json_obj["tunnus"].toString();
    QString enimi = json_obj["etunimi"].toString();
    QString snimi = json_obj["sukunimi"].toString();
    QString osoite = json_obj["osoite"].toString();
    QString puh_num = QString::number(json_obj["puhelinnumero"].toInt());

    reply->deleteLater();
    manager->deleteLater();

    emit showAsiakas(tunnus, enimi, snimi, osoite, puh_num);
}

void Restapi_DLL::asiakasInfo()
{
    qDebug()<<kirjautuneenAsiakkaanTunnus;
    QString site_url="http://localhost:3000/asiakas/"+kirjautuneenAsiakkaanTunnus;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getAsiakasSlot);

    reply = manager->get(request);
}

void Restapi_DLL::getKorttiSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();
    QString kortinnumero = json_obj["kortinnumero"].toString();
    QString pinkoodi = json_obj["pinkoodi"].toString();
    QString omistaja = json_obj["omistaja"].toString();
    QString tilinumero = json_obj["tilinumero"].toString();
    QString kortinlukija = json_obj["kortinlukija"].toString();

    reply->deleteLater();
    manager->deleteLater();

    emit showKortti(kortinnumero, pinkoodi, omistaja, tilinumero, kortinlukija);
}

void Restapi_DLL::korttiInfo()
{
    QString site_url="http://localhost:3000/kortti/"+kirjautuneenAsiakkaanKortinnumero;
    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getKorttiSlot);

    reply = manager->get(request);
}

void Restapi_DLL::getId(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    qDebug() << json_doc;
    QJsonObject json_obj = json_doc.object();

    //QJsonObject json_obj = json_doc.object();
    QString tunnus = json_obj["tunnus"].toString();
    QString kortinnumero = json_obj["kortinnumero"].toString();
    QString tilinumero = json_obj["tilinumero"].toString();
    QString nimi = json_obj["etunimi"].toString() + " " + json_obj["sukunimi"].toString();
    QString kortinlukija = json_obj["kortinlukija"].toString();
    qDebug() << "rest:" << tunnus << kortinnumero << tilinumero<< kortinlukija;

    kirjautuneenAsiakkaanKortinnumero=kortinnumero;
    kirjautuneenAsiakkaanTilinumero=tilinumero;
    kirjautuneenAsiakkaanTunnus=tunnus;

    emit sendId(tunnus,kortinnumero,tilinumero,nimi,kortinlukija);
    emit compareResult(true);
}



void Restapi_DLL::onLogin(QString kortti, QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("username","160006235F");
   // jsonObj.insert("username",kortti); //kortti
    jsonObj.insert("username",kortti); //kortti
    jsonObj.insert("password",pin);
    scannedCard=kortti;
    QString site_url="http://localhost:3000/login";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::loginSlot);
    reply = manager->post(request,QJsonDocument(jsonObj).toJson());
}

void Restapi_DLL::getToken(QByteArray tokenr)
{
    token = tokenr;
}

void Restapi_DLL::setId(QString tunnus, QString kortinnumero, QString tilinumero)
{
    kirjautuneenAsiakkaanTunnus = tunnus;
    kirjautuneenAsiakkaanKortinnumero =kortinnumero;
    kirjautuneenAsiakkaanTilinumero = tilinumero;
}

void Restapi_DLL::loginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;

    if(response_data == "false"){
        qDebug()<<"Tunnus tai salasana väärin";
        emit compareResult(false);

    }else
    {
        token ="Bearer "+response_data;

        qDebug()<<token;
        //emit compareResult(true);
        emit sendToken(token);


        //QString site_url="http://localhost:3000/kortti/"+scannedCard;  //environment::base_url+"/kortti/kirjautuneenAsiakkaanKortinnumero"
        QString site_url="http://localhost:3000/kortti/"+scannedCard;
        //QString site_url="http://localhost:3000/kortti/060006235F";  //environment::base_url+"/kortti/kirjautuneenAsiakkaanKortinnumero"
        //QString site_url="http://localhost:3000/kortti/0500CB33C7";
        QNetworkRequest request(site_url);
        //WEBTOKEN ALKU
        //QByteArray myToken="Bearer "+webToken;
        request.setRawHeader(QByteArray("Authorization"),(token));
        //WEBTOKEN LOPPU
        manager = new QNetworkAccessManager(this);

        connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getId);

        reply = manager->get(request);
    }
}



void Restapi_DLL::tilitapInfo()
{
    QString site_url="http://localhost:3000/tilitapahtumat/"+kirjautuneenAsiakkaanTilinumero;

    QNetworkRequest request(site_url);
    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+webToken;
    //qDebug()<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    //qDebug()<<token;
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getTilitapSlot);

    reply = manager->get(request);
}

void Restapi_DLL::getTilitapSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"gettilitap slotissa";
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonArray json_array = json_doc.array();
    qDebug()<<"Rest: "<<json_array;
    if(json_array.isEmpty())
    {
        emit errorSignal("tilitapahtumat is empty");
    }else
    {
    reply->deleteLater();
    manager->deleteLater();
    emit sendTilitapArray(json_array);
    }
}

void Restapi_DLL::tilitapPost(QString tapahtuma)
{
    QJsonObject jsonObj;

    qDebug()<<"tilitapPost: "<<talletus;

    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    qDebug()<<dateTime;
    jsonObj.insert("tilinumero",kirjautuneenAsiakkaanTilinumero);
    jsonObj.insert("kortinnumero",kirjautuneenAsiakkaanKortinnumero);
    jsonObj.insert("paivamaara",dateTime);
    jsonObj.insert("tapahtuma",tapahtuma);
    jsonObj.insert("summa",talletus);

    QString site_url="http://localhost:3000/tilitapahtumat";
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;

    request.setRawHeader(QByteArray("Authorization"),(token));

    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::addTilitapSlot);

    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void Restapi_DLL::addTilitapSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    manager->deleteLater();
}

void Restapi_DLL::deleteTilitap()
{
    QString site_url="http://localhost:3000/tilitapahtumat/"+kirjautuneenAsiakkaanTilinumero;

    QNetworkRequest request(site_url);

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+webToken;
    //qDebug()<<token;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    //qDebug()<<token;
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::deleteTilitapSlot);

    reply = manager->deleteResource(request);
}

void Restapi_DLL::deleteTilitapSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    manager->deleteLater();
}

void Restapi_DLL::tiliInfo()
{
    QString site_url="http://localhost:3000/tili/"+kirjautuneenAsiakkaanTilinumero;
    QNetworkRequest request(site_url);

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getTiliSlot);

    reply = manager->get(request);
}

void Restapi_DLL::getSaldoSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << "DATA : " + response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString saldo = json_obj["saldo"].toString();

    emit showSaldo(saldo);
    reply->deleteLater();
    manager->deleteLater();
}

void Restapi_DLL::saldoInfo()
{
    QString site_url="http://localhost:3000/tili/"+kirjautuneenAsiakkaanTilinumero;
    QNetworkRequest request(site_url);

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;
    request.setRawHeader(QByteArray("Authorization"),(token));
    //WEBTOKEN LOPPU
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getSaldoSlot);

    reply = manager->get(request);
}

void Restapi_DLL::getLoginSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<"DATA : "+response_data;
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    qDebug()<<"doc : "<<json_doc;
    QJsonArray json_array = json_doc.array();
    qDebug()<<"array : "<<json_array;

    const QJsonValue &value = json_array;
    QJsonObject json_obj = value.toObject();
}

void Restapi_DLL::loginInfo()
{
    QString site_url="http://localhost:3000/login";
    QNetworkRequest request(site_url);
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::getLoginSlot);

    reply = manager->get(request);
}

void Restapi_DLL::tiliUpdate(QString summa)
{
    talletus=summa;
    qDebug()<<"tili updatessa";
    QString site_url="http://localhost:3000/tili/"+kirjautuneenAsiakkaanTilinumero;
    QNetworkRequest request(site_url);

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;

    request.setRawHeader(QByteArray("Authorization"),(token));

    //WEBTOKEN LOPPU
    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::handleTiliUpdate);
    reply = manager->get(request);
}

void Restapi_DLL::handleTiliUpdate()
{
    qDebug()<<"handleTiliUpdatessa";
    response_data = reply->readAll();
    qDebug() << "DATA : " + response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();

    //QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    QJsonObject json_obj = json_doc.object();

    QString tilinumero = json_obj["tilinumero"].toString();
    QString saldo = json_obj["saldo"].toString();
    QString omistaja = json_obj["omistaja"].toString();
    QString luottoraja = json_obj["luottoraja"].toString();
    double num1=saldo.toDouble();
    float num2=talletus.toFloat();
    qDebug()<<num1;
    qDebug()<<num2;
    float summa=num1+num2;
    QString tapahtuma;
    if(num2<0)
    {
        tapahtuma="nosto";
    }else tapahtuma="talletus";


    if(summa<0)
    {

        if(summa >= -luottoraja.toDouble()){
            QString newTalletus=QString::number(summa);
            qDebug()<<newTalletus;

            QJsonObject jsonObj;
            jsonObj.insert("tilinumero",kirjautuneenAsiakkaanTilinumero);
            jsonObj.insert("saldo",newTalletus);
            jsonObj.insert("omistaja",kirjautuneenAsiakkaanTunnus);
            jsonObj.insert("luottoraja",luottoraja);

            QString site_url="http://localhost:3000/tili/"+kirjautuneenAsiakkaanTilinumero;
            QNetworkRequest request(site_url);
            request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

            //WEBTOKEN ALKU
            //QByteArray myToken="Bearer "+token;

            request.setRawHeader(QByteArray("Authorization"),(token));

            //WEBTOKEN LOPPU

            manager = new QNetworkAccessManager(this);
            connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::updateTiliSlot);

            reply = manager->put(request, QJsonDocument(jsonObj).toJson());

            tilitapPost(tapahtuma);
}else qDebug()<<"Tilillä liian vähän rahaa";
    }
    else
    {
    QString newTalletus=QString::number(summa);
    qDebug()<<newTalletus;

    QJsonObject jsonObj;
    jsonObj.insert("tilinumero",kirjautuneenAsiakkaanTilinumero);
    jsonObj.insert("saldo",newTalletus);
    jsonObj.insert("omistaja",kirjautuneenAsiakkaanTunnus);
    jsonObj.insert("luottoraja",luottoraja);

    QString site_url="http://localhost:3000/tili/"+kirjautuneenAsiakkaanTilinumero;
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;

    request.setRawHeader(QByteArray("Authorization"),(token));

    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::updateTiliSlot);

    reply = manager->put(request, QJsonDocument(jsonObj).toJson());

    tilitapPost(tapahtuma);
    }
}

void Restapi_DLL::updateTiliSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    manager->deleteLater();
}

void Restapi_DLL::lockCard()
{
    QString site_url="http://localhost:3000/login/"+scannedCard;
    QNetworkRequest request(site_url);
    qDebug()<<"rest: "<<kirjautuneenAsiakkaanKortinnumero;
    qDebug()<<"rest: "<<kirjautuneenAsiakkaanTilinumero;

    manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::lockCardSlot);
    reply = manager->get(request);
}

void Restapi_DLL::lockCardSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << "DATA lockCard: " + response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    //QJsonArray json_array = json_doc.array();

    //QJsonDocument json_doc = QJsonDocument::fromJson(response_data);

    QJsonObject json_obj = json_doc.object();

    QString pinkoodi = json_obj["pinkoodi"].toString();
    QString kortinnumero = json_obj["kortinnumero"].toString();
    QString omistaja = json_obj["omistaja"].toString();
    QString tilinumero = json_obj["tilinumero"].toString();
    QString kortinlukija = json_obj["kortinlukija"].toString();

    QJsonObject jsonObj;
    jsonObj.insert("kortinnumero",scannedCard);
    jsonObj.insert("pinkoodi",pinkoodi);
    jsonObj.insert("omistaja",omistaja);
    jsonObj.insert("tilinumero",tilinumero);
    jsonObj.insert("kortinlukija","lukittu");

    qDebug()<<jsonObj;

    QString site_url="http://localhost:3000/login/"+scannedCard;
    QNetworkRequest request(site_url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    //QByteArray myToken="Bearer "+token;

    //request.setRawHeader(QByteArray("Authorization"),(token));

    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Restapi_DLL::updateLockSlot);

    reply = manager->put(request, QJsonDocument(jsonObj).toJson());
}

void Restapi_DLL::updateLockSlot(QNetworkReply *reply)
{
    response_data=reply->readAll();
    qDebug()<<response_data;
    reply->deleteLater();
    manager->deleteLater();
}



void Restapi_DLL::getTiliSlot(QNetworkReply *reply)
{
    response_data = reply->readAll();
    qDebug() << "DATA : " + response_data;

    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    QJsonObject json_obj = json_doc.object();

    QString tilinumero = json_obj["tilinumero"].toString();
    QString saldo = json_obj["saldo"].toString();
    QString omistaja = json_obj["omistaja"].toString();
    QString luottoraja = json_obj["luottoraja"].toString();

    emit showTili(tilinumero,saldo,omistaja,luottoraja);
    reply->deleteLater();
    manager->deleteLater();
}
