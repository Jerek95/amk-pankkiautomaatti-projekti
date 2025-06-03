#ifndef TILITAP_H
#define TILITAP_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

namespace Ui {
class tilitap;
}

class tilitap : public QDialog
{
    Q_OBJECT

public:
    explicit tilitap(QWidget *parent = nullptr);
    ~tilitap();
    Ui::tilitap *ui;
    void setJsonArray(QJsonArray);
    void setLineEdits();

private slots:
    void handleNext();
    void handleprevious();

private:
    QJsonArray json_array;
    QString tilinumero;
    QString kortinnumero;
    QString paivamaara;
    QString tapahtuma;
    double sum;
    QString summa;
    int clicks=0;
};

#endif // TILITAP_H
