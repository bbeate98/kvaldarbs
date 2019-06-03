#include "dzest.h"
#include "ui_dzest.h"

dzest::dzest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dzest)
{
    ui->setupUi(this);
    paradit_personas();
    paradit_amatus();
    paradit_adreses();
    paradit_ligumus();
    paradit_pers_bil();
    paradit_piekluves();
}

dzest::~dzest()
{
    delete ui;
}

//funkcija parāda sistemā pieejamās personas, kuras var izdzēst
void dzest::paradit_personas(){
   QVector<QString> vardiuzvardi;
   vardiuzvardi=mw.db.vardsuzvards1(ID1);
   ui->dzestpersonas->clear();
   for (int i=0; i<vardiuzvardi.size(); i++){
       ui->dzestpersonas->addItem(vardiuzvardi[i]);
   }

}
//funkcija parāda sistemā pieejamās personas, kurām ir pievienotas bildes
void dzest::paradit_pers_bil(){

    QVector<QString> vardiuzvardi1;
    vardiuzvardi1=mw.db.vardsuzvards_irbildes(ID2);
    ui->dzestbildes->clear();
    for (int i=0; i<vardiuzvardi1.size(); i++){
        ui->dzestbildes->addItem(vardiuzvardi1[i]);
    }

}
//funkcija parāda sistemā pieejamos amatus, kas nevienam vēl nav pievienoti
void dzest::paradit_amatus(){
    QVector<QString> amati;
    amati=mw.db.neizmantotie_amati(ID5);
    ui->dzestamatu->clear();
    for (int i=0; i<amati.size(); i++){
        ui->dzestamatu->addItem(amati[i]);
    }
}
//funkcija parāda sistemā pieejamās adreses, kuras vēl nav nevienam pievienotas un tādējādi tās var dzēst
void dzest::paradit_adreses(){

    QVector<QString> adreses;
    adreses=mw.db.neizmantotas_adreses(ID3);
    ui->dzestadreses->clear();
    for (int i=0; i<adreses.size(); i++){
        ui->dzestadreses->addItem(adreses[i]);
    }

}
//funkcija parāda sistēmā esošos līgumus, kuri nav pievienoti nevienai persoani pašlaik
void dzest::paradit_ligumus(){

    QVector<QString> ligumi;
    ligumi=mw.db.neizmantotie_ligumi(ID4);
    ui->dzestligumu->clear();
    for (int i=0; i<ligumi.size(); i++){
        ui->dzestligumu->addItem(ligumi[i]);
    }

}

void dzest::paradit_piekluves(){

    QVector<QString> piekluves;
    piekluves=mw.db.piekluves(ID6);
    ui->dzestpiekluvi->clear();
    for (int i=0; i<piekluves.size(); i++){
        ui->dzestpiekluvi->addItem(piekluves[i]);
    }
}
//izdzēs personas bildes
void dzest::on_dzest_bildes_clicked()
{
    int perso= ui->dzestbildes->currentIndex();
    int pes=ID2[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šīs personas bildes?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_personas_bildes(pes);
        paradit_pers_bil();
    }

}
//izdzēs personu
void dzest::on_dzest_personu_clicked()
{
    int perso= ui->dzestpersonas->currentIndex();
    int pes=ID1[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šo personu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_personas_bildes(pes);
        mw.db.dzest(pes);
        paradit_personas();
    }
}
//izdzēš adresi
void dzest::on_dzest_adresi_clicked()
{
    int perso= ui->dzestadreses->currentIndex();
    int pes=ID3[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šo adresi?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_adresi(pes);
        paradit_adreses();
    }
}

//izdzēs ligumu
void dzest::on_dzest_ligumu_clicked()
{
    int perso= ui->dzestligumu->currentIndex();
    int pes=ID4[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šo līgumu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_ligumu(pes);
        paradit_ligumus();
    }
}
//izdzēs amatu
void dzest::on_dzest_amatu_clicked()
{
    int perso= ui->dzestamatu->currentIndex();
    int pes=ID5[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šo amatu?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_amatu(pes);
        paradit_amatus();
    }
}
//izdzēs piekļuvi
void dzest::on_dzest_piekluvi_clicked()
{
    int perso= ui->dzestpiekluvi->currentIndex();
    int pes=ID6[perso];
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies dzēst šo piekļuvi?"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        mw.db.dzest_piekluvi(pes);
        paradit_piekluves();
    }
}
