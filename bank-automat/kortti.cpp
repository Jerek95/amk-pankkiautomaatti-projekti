#include "kortti.h"
#include "ui_kortti.h"

kortti::kortti(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::kortti)
{
    ui->setupUi(this);
}

kortti::~kortti()
{
    delete ui;
}
