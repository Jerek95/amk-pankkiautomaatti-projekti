#include "asiakas.h"
#include "ui_asiakas.h"

Asiakas::Asiakas(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Asiakas)
{
    ui->setupUi(this);
}

Asiakas::~Asiakas()
{
    delete ui;
}
