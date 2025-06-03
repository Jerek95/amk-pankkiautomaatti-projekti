#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_retrievalButton_clicked();
    void getAsiakasSlot (QNetworkReply *reply);
    void on_tilitapButton_clicked();
    void getTilitapSlot(QNetworkReply *reply);
    void on_tilitapPostButton_clicked();
    void addTilitapSlot(QNetworkReply *reply);


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray response_data;
};
#endif // MAINWINDOW_H
