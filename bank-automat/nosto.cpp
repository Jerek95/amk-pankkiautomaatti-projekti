#include "nosto.h"
#include "ui_nosto.h"

nosto::nosto(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::nosto)
{
    ui->setupUi(this);
    connect(ui->sendButton,&QPushButton::clicked,this,&nosto::handleNostoButton);
}

nosto::~nosto()
{
    delete ui;
}

void nosto::handleNostoButton()
{
    if(ui->nostaLineEdit->text().contains("-"))
    {
        QMessageBox objMessageBox;
        objMessageBox.setText("- ei ole sallittu");
        objMessageBox.exec();
    }
    else
    {
    QString summa = "-"+ui->nostaLineEdit->text();
    emit sendNostoSignal(summa);
    ui->nostaLineEdit->setText("");
    }
}
