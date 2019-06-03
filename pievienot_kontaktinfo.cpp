#include "pievienot_kontaktinfo.h"
#include "ui_pievienot_kontaktinfo.h"
#include "QMessageBox"

pievienot_kontaktinfo::pievienot_kontaktinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pievienot_kontaktinfo)
{
    ui->setupUi(this);
    personas();
    amati();
    ligumi();
    adrese();
}

pievienot_kontaktinfo::~pievienot_kontaktinfo()
{
    delete ui;
}

//funkcija, lai pievienotu jaunu kontaktinformāciju
void pievienot_kontaktinfo::on_pievienot_kontakt_clicked()
{
    QString tel= ui->tel_nr->text();
    QDate dzimsanas_dat= ui->dzimsanas_datums->date();
    int perso= ui->pers_ID->currentIndex();
    int amat=ui->Amats_ID->currentIndex();
    int ligu= ui->lig_ID->currentIndex();
    int adre= ui->Amats_ID->currentIndex();
    int index_pers=index[perso];
    int index_amat=index_2[amat];
    int index_lig=index_3[ligu];
    int index_andr=index_4[adre];

    if (tel.size()==0) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
     else{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies pievienot šo "),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.pievienot_kontaktinfo(tel, dzimsanas_dat, index_pers, index_andr, index_amat, index_lig);

        close();
    }

    if(reply == QMessageBox::Cancel)
    {
        close();
    }
}
}


void pievienot_kontaktinfo::personas(){
    QVector<QString> vu;
    vu=mw.db.vardsuzvards_kinfo(index);
    ui->pers_ID->clear();
    for (int i=0; i<vu.size(); i++){
        ui->pers_ID->addItem(vu[i]);
    }
}

void pievienot_kontaktinfo::amati(){
    QVector<QString> amati;
    amati=mw.db.amati(index_2);
    ui->Amats_ID->clear();
    for (int i=0; i<amati.size(); i++){
        ui->Amats_ID->addItem(amati[i]);
    }
}

void pievienot_kontaktinfo::ligumi(){
    QVector<QString> lig;
    lig=mw.db.ligumi(index_3);
    ui->lig_ID->clear();
    for (int i=0; i<lig.size(); i++){
        ui->lig_ID->addItem(lig[i]);
    }
}

void pievienot_kontaktinfo::adrese(){
    QVector<QString> adr;
    adr=mw.db.adrese(index_4);
    ui->Adrese->clear();
    for (int i=0; i<adr.size(); i++){
        ui->Adrese->addItem(adr[i]);
    }
}

