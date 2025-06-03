#include "tili.h"
#include "ui_tili.h"

tili::tili(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::tili)
{
    ui->setupUi(this);
}

tili::~tili()
{
    delete ui;
}
