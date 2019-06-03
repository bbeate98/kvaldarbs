#include "pievienot_ligums.h"
#include "ui_pievienot_ligums.h"
#include <QMessageBox>
#include <QDate>

pievienot_ligums::pievienot_ligums(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pievienot_ligums)
{
    ui->setupUi(this);
}

pievienot_ligums::~pievienot_ligums()
{
    delete ui;
}
//funkcija, lai pievienotu līgumu datubāzei
void pievienot_ligums::on_pievienot_lig_clicked()
{

    QString lig_nr=ui->lig_nr->text();
    int slodze= ui->spinBox->value();
    QDate sak_dat= ui->mosl_datums->date();
    QDate beig_dat= ui->mosl_datums_2->date();
    if ((lig_nr.size()==0||slodze==0)) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
     else{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies pievienot šādu līgumu : %1")
                                  .arg(lig_nr),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {

        mw.db.pievienot_ligumu(lig_nr,sak_dat,slodze,beig_dat);
        close();
    }

    if(reply == QMessageBox::Cancel)
    {
        close();
    }
    }
}
