#include "pievienot_amatu.h"
#include "ui_pievienot_amatu.h"
#include <QMessageBox>


pievienot_amatu::pievienot_amatu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pievienot_amatu)
{
    ui->setupUi(this);
}

pievienot_amatu::~pievienot_amatu()
{
    delete ui;
}
//funkcija, lai pievienotu datu bāzei jaunu amatu
void pievienot_amatu::on_pievienot_amats_clicked()
{

    QString nosaukums=ui->nosaukums->text();
    QString apraksts=ui->apraksts->text();

    QMessageBox::StandardButton reply;
    if (nosaukums.size()==0) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
     else{
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies pievienot šādu amatu : %1")
                                  .arg(nosaukums),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {

        mw.db.pievienot_amatu(nosaukums,apraksts);
        close();
    }

    if(reply == QMessageBox::Cancel)
    {
        close();
    }
}
}
