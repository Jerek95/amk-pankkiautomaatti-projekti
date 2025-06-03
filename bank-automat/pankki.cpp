#include "pankki.h"
#include "ui_pankki.h"
#include "asiakas.h"
#include "kortti.h"
#include "ui_asiakas.h"
#include "ui_kortti.h"
#include "tili.h"
#include "ui_tili.h"
#include "ui_tilitap.h"
#include "saldo.h"
#include "ui_saldo.h"

pankki::pankki(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::pankki)
{
    ui->setupUi(this);
    rest_api = new Restapi_DLL(this);
    talletus_ui =new talletus(this);
    nosto_ui = new nosto(this);

    connect(ui->pushButtonAsiakas, &QPushButton::clicked, rest_api, &Restapi_DLL::asiakasInfo);
    connect(ui->pushButtonKortti, &QPushButton::clicked, rest_api, &Restapi_DLL::korttiInfo);
    connect(ui->pushButtonTilitap,&QPushButton::clicked, rest_api, &Restapi_DLL::tilitapInfo);
    connect(ui->pushButtonTili,&QPushButton::clicked, rest_api, &Restapi_DLL::tiliInfo);
    connect(ui->pushButtonSaldo,&QPushButton::clicked, rest_api, &Restapi_DLL::saldoInfo);
    connect(ui->kirjauduUlosButton,&QPushButton::clicked, this, &pankki::handleKirjauduUlos);
    connect(ui->talletaRahaaButton,&QPushButton::clicked, this, &pankki::handleTalletus);
    connect(ui->nostaRahaaButton,&QPushButton::clicked, this, &pankki::handleNosto);
    connect(talletus_ui,&talletus::sendTalletusSum, this, &pankki::handleTalletusSignal);
    connect(nosto_ui,&nosto::sendNostoSignal, this, &pankki::handleTalletusSignal);

    connect(rest_api, &Restapi_DLL::showAsiakas, this, &pankki::handleAsiakasSignal);
    connect(rest_api, &Restapi_DLL::showKortti, this, &pankki::handleKorttiSignal);
    connect(rest_api, &Restapi_DLL::showTili, this, &pankki::handleTiliSignal);
    connect(rest_api, &Restapi_DLL::showSaldo, this, &pankki::handleSaldoSignal);
    connect(rest_api, &Restapi_DLL::sendTilitapArray, this, &pankki::handleTilitapArray);
    connect(rest_api, &Restapi_DLL::errorSignal, this, &pankki::handleErrorSignal);
    asiakas_ui = new Asiakas(this);
    kortti_ui = new kortti(this);
    tili_ui = new tili(this);
    tilitapahtumat_ui =new tilitap(this);
    saldo_ui = new saldo(this);

    show();
}

pankki::~pankki()
{
    delete ui;
}

void pankki::setToken(QByteArray tokenr)
{
    token = tokenr;
    qDebug()<<"pankki";
    qDebug()<<token;
    rest_api->getToken(token);
}

void pankki::setId(QString tunnusr, QString kortinnumeror, QString tilinumeror, QString nimir)
{
    tunnus = tunnusr;
    kortinnumero=kortinnumeror;
    tilinumero=tilinumeror;
    nimi = nimir;
    qDebug()<<"pankki: "<<tunnus<<kortinnumero<<tilinumero;
    rest_api->setId(tunnus,kortinnumero,tilinumero);
}

void pankki::handleAsiakasSignal(QString tunnus, QString enimi, QString snimi, QString osoite, QString puh_num)
{
    qDebug()<<"avataan asiakkaan tiedot";

    asiakas_ui->ui->lineEditTunnus->setText(tunnus);
    asiakas_ui->ui->lineEditENimi->setText(enimi);
    asiakas_ui->ui->lineEditSNimi->setText(snimi);
    asiakas_ui->ui->lineEditOsoite->setText(osoite);
    asiakas_ui->ui->lineEditPuhnum->setText(puh_num);

    asiakas_ui->show();
}

void pankki::handleKorttiSignal(QString kortinnumero, QString pinkoodi, QString omistaja, QString tilinumero, QString kortinlukija)
{
    qDebug()<<"avataan kortin tiedot";

    kortti_ui->ui->lineEditKornum->setText(kortinnumero);
    //kortti_ui->ui->lineEditPin->setText(pinkoodi);
    kortti_ui->ui->lineEditOmistaja->setText(nimi);
    kortti_ui->ui->lineEditTilinum->setText(tilinumero);
    //kortti_ui->ui->lineEditKorluk->setText(kortinlukija);

    kortti_ui->show();
}


void pankki::handleTiliSignal(QString tilinumero, QString saldo, QString omistaja, QString luottoraja)
{
    qDebug()<<"avataan tilin tiedot";

    tili_ui->ui->tilinumeroJoho->setText(tilinumero);
    tili_ui->ui->saldoJoho->setText(saldo);
    tili_ui->ui->omistajaJoho->setText(nimi);
    tili_ui->ui->luottorajaJoho->setText(luottoraja);

    tili_ui->show();
}

void pankki::handleSaldoSignal(QString s)
{
    saldo_ui->ui->lineEditSaldo->setText(s);

    saldo_ui->show();
}

void pankki::handleToken()
{

}

void pankki::handleTilitapArray(QJsonArray json_array)
{

    //qDebug()<<"array : "<<json_array;
    //QJsonObject json_obj = json_array[0].toObject();
    //qDebug()<<"Pankki: "<<json_array;

    tilitapahtumat_ui->setJsonArray(json_array);
    tilitapahtumat_ui->setLineEdits();
}

void pankki::handleKirjauduUlos()
{
    //tähän koodi jolla poistetaan tilitapahtumat tietokannasta
    emit kirjauduUlosSignal();
    //rest_api->deleteTilitap();
    close();
}

void pankki::handleTalletus()
{
    talletus_ui->show();
}

void pankki::handleTalletusSignal(QString summa)
{
    qDebug()<<"signaali vastaanotettu";

    rest_api->tiliUpdate(summa);
    talletus_ui->close();
    nosto_ui->close();
}

void pankki::handleNosto()
{
    nosto_ui->show();
}

void pankki::handleErrorSignal(QString error)
{
    QMessageBox objMessageBox;
    objMessageBox.setText(error);
    objMessageBox.exec();
}

