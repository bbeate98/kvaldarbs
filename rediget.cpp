#include "rediget.h"
#include "ui_rediget.h"
#include "QMessageBox"

rediget::rediget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rediget)
{
    ui->setupUi(this);
    paradit_personas();
}

rediget::~rediget()
{
    delete ui;
}

void rediget::on_pushButton_clicked()
{
 paradit_info();
}

void rediget::paradit_info(){

    ui->lig->clear();
    ui->adrese->clear();
    ui->amats->clear();
    ui->tel_nr->clear();
    ui->dz_dat->clear();

    int ID =ui->paraditpersonas->currentIndex();
    personas_ID=ID1[ID];

    QString vards, uzvards, ligums, amats, adrese, tel_nr;
    QDate dz_dat;
    mw.db.visi_dati(personas_ID, vards, uzvards,tel_nr, amats, ligums,dz_dat, adrese);
    ui->vards_2->setText(vards);
    ui->uzvards->setText(uzvards);

    ui->dz_dat->setDate(dz_dat);

    if (tel_nr.size()!=0){
        ui->tel_nr->setText(tel_nr);
    }

    int a=1;
    if (dz_dat.isNull()) a=0;
    if (a==1){
        ui->tel_nr->setText(tel_nr);
    }

    if(ligums.size()!=0){
        ui->lig->addItem(ligums);
        QVector<QString> ligumi;
        ligumi=mw.db.neizmantotie_ligumi(ID2);
        for (int i=0; i<ligumi.size(); i++){
            if(ligums!=ligumi[i])
            ui->lig->addItem(ligumi[i]);
        }
    }
    QString ad=" , , ";
    if(adrese!=ad){
        ui->adrese->addItem(adrese);
        QVector<QString> adreses;
        adreses=mw.db.adrese(ID3);
        for (int i=0; i<adreses.size(); i++){
            if (adrese!=adreses[i]){
            ui->adrese->addItem(adreses[i]);}
        }
    }

    if(amats.size()!=0){

        ui->amats->addItem(amats);
        QVector<QString> amati;
        amati=mw.db.amati(ID4);
        for (int i=0; i<amati.size(); i++){
            if(amats!=amati[i])
            ui->amats->addItem(amati[i]);
        }
    }



}

//parāda pieejamās personas, kuras var rediģet
void rediget::paradit_personas(){
    QVector<QString> vardiuzvardi;
    vardiuzvardi=mw.db.vardsuzvards1(ID1);
    ui->paraditpersonas->clear();
    for (int i=0; i<vardiuzvardi.size(); i++){
        ui->paraditpersonas->addItem(vardiuzvardi[i]);
    }
}

//funkcija, kas ļauj rediģēt vārdu
void rediget::on_red_vardu_clicked()
{
    QString vards= ui->vards_2->text();
    if(vards.size()!=0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas vārdu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            mw.db.rediget_vardu(personas_ID, vards);
            paradit_info();
        }

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}
}

//funkcija, kas ļauj rediģēt uzvārdu
void rediget::on_rediget_uzvardu_clicked()
{
    QString uzvards= ui->uzvards->text();
    if(uzvards.size()!=0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas uzvādu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            mw.db.rediget_uzvardu(personas_ID, uzvards);
            paradit_info();
        }
    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}
}

//funkcija, kasļauj rediģēt telefona nummuru
void rediget::on_rediget_telefona_nummuru_clicked()
{
    QString telefonanum= ui->tel_nr->text();
    if(telefonanum.size()!=0){        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas telefona nummuru?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {

            mw.db.rediget_telefons(personas_ID, telefonanum);
            paradit_info();

        }

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}
}

//funkcija, kas ļauj rediģēt dzimšanas datumu
void rediget::on_rediget_dzimsanas_datumu_clicked()
{
    QDate dzimsanas_dat= ui->dz_dat->date();
    mw.db.rediget_dzimsanas_datumu(personas_ID, dzimsanas_dat);
    paradit_info();
}

//funkcija, kas ļauj rediģēt personas amatu
void rediget::on_rediget_amatu_clicked()
{
    int perso= ui->amats->currentIndex();
    if (perso!=0){
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas amatu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            int index_pers=ID4[perso-1];
            mw.db.rediget_amatu(personas_ID,index_pers);
            paradit_info();

        }


    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}

}
//funkcija, kas ļauj rediģēt personas līguma nummuru
void rediget::on_rediget_ligumu_clicked()
{
    int perso= ui->lig->currentIndex();
    if (perso!=0){
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas līgumu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            int index_pers=ID2[perso-1];
            mw.db.rediget_ligumu(personas_ID,index_pers);
            paradit_info();
        }

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}
}

//funkcija, kas ļauj rediģēt personas adresi
void rediget::on_rediget_adresi_clicked()
{
    int perso= ui->adrese->currentIndex();
    if (perso!=0){

        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies rediģēt šīs personas adresi?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
            int index_pers=ID3[perso-1];
            mw.db.rediget_adresi(personas_ID,index_pers);
            paradit_info();
        }

    }
    else{
        QMessageBox msgBox;
        msgBox.setText("Nav korekti ievadīti dati!");
        msgBox.setWindowTitle(" ");
        msgBox.exec();}

}
