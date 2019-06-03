#include "pievienot.h"
#include "ui_pievienot.h"
#include "QString"
#include <iostream>
#include <QProgressBar>
#include "mainwindow.h"

using namespace std;
using namespace cv;

Pievienot::Pievienot(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pievienot)
{
    ui->setupUi(this);

}

Pievienot::~Pievienot()
{
    delete ui;
}


void Pievienot::on_pushButton_clicked()
{
    QString vards=ui->lineEdit->text(); //iegūst ievadīto personas vārdu
    QString uzvards=ui->lineEdit_2->text(); //iegūst ievadīto personas uzvārdu
if ((vards.size()==0||uzvards.size()==0)) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
else{

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies pievienot %1 %2 datubāzei")
                                  .arg(vards).arg(uzvards),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        MainWindow mw;
        mw.db.pievienot_cilveku(vards, uzvards);//ja dialoglodziņā nopsiež "Ok" ppievieno personu datubāzei
        close();
    }

    if(reply == QMessageBox::Cancel)
    {
        close();
    }
}
}


