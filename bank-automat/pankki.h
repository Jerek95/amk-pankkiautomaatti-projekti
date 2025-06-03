#ifndef PANKKI_H
#define PANKKI_H

#include <QDialog>
#include "restapi_dll.h"
#include "asiakas.h"
#include "kortti.h"
#include "tili.h"
#include "tilitap.h"
#include "talletus.h"
#include "nosto.h"
#include "saldo.h"
#include <QMessageBox>

namespace Ui {
class pankki;
}

class pankki : public QDialog
{
    Q_OBJECT

public:
    explicit pankki(QWidget *parent = nullptr);
    ~pankki();
    Asiakas* asiakas_ui;
    kortti* kortti_ui;
    tili* tili_ui;
    tilitap* tilitapahtumat_ui;
    talletus* talletus_ui;
    nosto* nosto_ui;
    saldo* saldo_ui;
    void setId(QString,QString,QString,QString);
    void setToken(QByteArray);

private:
    Ui::pankki *ui;
    Restapi_DLL* rest_api;
    QByteArray token;
    QString tunnus;
    QString kortinnumero;
    QString tilinumero;
    QString nimi;

private slots:
    void handleAsiakasSignal(QString, QString, QString, QString, QString);
    void handleKorttiSignal(QString, QString, QString, QString, QString);
    void handleTiliSignal(QString, QString, QString, QString);
    void handleSaldoSignal(QString);
    void handleToken();
    void handleTilitapArray(QJsonArray);
    void handleKirjauduUlos();
    void handleTalletus();
    void handleTalletusSignal(QString);
    void handleNosto();
    void handleErrorSignal(QString);

signals:
    void kirjauduUlosSignal();
};

#endif // PANKKI_H
