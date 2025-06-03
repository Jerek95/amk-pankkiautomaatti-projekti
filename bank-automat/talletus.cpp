#include "talletus.h"
#include "ui_talletus.h"

talletus::talletus(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::talletus)
{
    ui->setupUi(this);
    connect(ui->sendButton,&QPushButton::clicked,this,&talletus::handlesendButton);
}

talletus::~talletus()
{
    delete ui;
}

void talletus::handlesendButton()
{
    if(ui->talletusLineEdit->text().contains("-"))
    {
        QMessageBox objMessageBox;
        objMessageBox.setText("- ei ole sallittu");
        objMessageBox.exec();
        qDebug()<<"jatkuu execin jälkeen";
    }
    else
    {
    qDebug()<<"emitting talletus";
    emit sendTalletusSum(ui->talletusLineEdit->text());
    ui->talletusLineEdit->setText("");
    }
}
