#ifndef RESTAPI_DLL_H
#define RESTAPI_DLL_H

#include "restapi_DLL_global.h"
#include <QDialog>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QDateTime>


class RESTAPI_DLL_EXPORT Restapi_DLL : public QObject
{
    Q_OBJECT
public:
    Restapi_DLL(QObject * parent = nullptr);

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
    QString kirjautuneenAsiakkaanTunnus;
    QString kirjautuneenAsiakkaanKortinnumero;
    QString kirjautuneenAsiakkaanTilinumero;
    QByteArray token;
    QByteArray atoken;
    QString scannedCard;
    QString talletus;

public:
    void onLogin(QString,QString);
    void getToken(QByteArray);
    void setId(QString,QString,QString);

public slots:
    void getAsiakasSlot (QNetworkReply *reply);
    void asiakasInfo();
    void getKorttiSlot (QNetworkReply *reply);
    void korttiInfo();
    void getId(QNetworkReply *reply);
    void loginSlot(QNetworkReply *reply);
    void tilitapInfo();
    void getTilitapSlot(QNetworkReply *reply);
    void tilitapPost(QString);
    void addTilitapSlot(QNetworkReply *reply);
    void deleteTilitap();
    void deleteTilitapSlot(QNetworkReply *reply);
    void getTiliSlot (QNetworkReply *reply);
    void tiliInfo();
    void getSaldoSlot(QNetworkReply *reply);
    void saldoInfo();
    void getLoginSlot (QNetworkReply *reply);
    void loginInfo();
    void tiliUpdate(QString);
    void handleTiliUpdate();
    void updateTiliSlot(QNetworkReply *reply);
    void lockCard();
    void lockCardSlot(QNetworkReply *reply);
    void updateLockSlot(QNetworkReply *reply);

signals:
    void showAsiakas(QString, QString, QString, QString, QString);
    void showKortti(QString, QString, QString, QString, QString);
    void showTili(QString, QString, QString, QString);
    void showSaldo(QString);
    void sendPin(QString);
    void compareResult(bool);
    void sendTilitapArray(QJsonArray);
    void sendToken(QByteArray);
    void sendId(QString, QString, QString, QString,QString);
    void errorSignal(QString);
};

#endif // RESTAPI_DLL_H
