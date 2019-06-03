#include "skatit_pers.h"
#include "ui_skatit_pers.h"
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "QString"
#include "QVector"
#include "QFont"
#include <QStandardItemModel>
#include <iomanip>
#include "QMessageBox"

skatit_pers::skatit_pers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::skatit_pers)
{
    ui->setupUi(this);

    paradit();
    paradit_personas();

}

//funkcija, kas parāda atbilstošos datus irmajos trīs tabulu skatos
void skatit_pers::paradit(){

    QSqlQueryModel *model = new QSqlQueryModel (ui->tableView);
    model->setQuery ("SELECT Persona.vards AS Vārds, Persona.uzvards AS Uzvārds,  "
                     " Kontaktinformacija.Telefona_nr AS Telefona_nummurs, Amats.nosaukums AS Amata_nosaukums,"
                     " Ligums.lig_nummurs AS Līguma_nummurs, Adrese.iela AS Adrese_iela, Adrese.majas_dzivokla_nummurs AS Nummurs, "
                     "Adrese.pilseta AS Pilsēta,  Adrese.pasta_indekss AS Pasts_indekss FROM Kontaktinformacija "
                     "LEFT JOIN Persona ON Kontaktinformacija.ID_persona = Persona.ID "
                     "LEFT JOIN Amats ON Kontaktinformacija.ID_amats = Amats.ID_am L"
                     "EFT JOIN Ligums ON Kontaktinformacija.ID_ligums = Ligums.ID_lig "
                     "LEFT JOIN Adrese ON Kontaktinformacija.ID_adrese = Adrese.ID_ad "
                     "UNION ALL "
                     "SELECT Persona.vards AS Vārds, Persona.uzvards AS Uzvārds, "
                     " Kontaktinformacija.Telefona_nr AS Telefona_nummurs, "
                     "Amats.nosaukums AS Amata_nosaukums, Ligums.lig_nummurs AS Līguma_nummurs, Adrese.iela AS Adrese_iela, "
                     "Adrese.majas_dzivokla_nummurs AS Nummurs, Adrese.pilseta AS Pilsēta,  Adrese.pasta_indekss AS Pasts_indekss "
                     "FROM Persona LEFT JOIN Kontaktinformacija ON Persona.ID = Kontaktinformacija.ID_persona "
                     "LEFT JOIN Amats ON Kontaktinformacija.ID_amats = Amats.ID_am "
                     "LEFT JOIN Ligums ON Kontaktinformacija.ID_ligums = Ligums.ID_lig "
                     "LEFT JOIN Adrese ON Kontaktinformacija.ID_adrese = Adrese.ID_ad "
                     "WHERE Kontaktinformacija.ID_persona IS NULL OR Kontaktinformacija.ID_adrese IS NULL "
                     "OR Kontaktinformacija.ID_amats IS NULL OR Kontaktinformacija.ID_ligums is NULL "
"order By Persona.uzvards");

    ui->tableView->setModel(model);
    ui->tableView->resizeColumnsToContents();

    QVector<QString> vu;
    vu=mw.db.vardsuzvards();
    ui->comboBox->clear();
    for (int i=0; i<vu.size(); i++){
        ui->comboBox->addItem(vu[i]);
    }

    QSqlQueryModel *model1 = new QSqlQueryModel (ui->tableView_2);
    model1->setQuery ("Select vards AS Vārds ,uzvards AS Uzvārds FROM Persona WHERE irdarba=1");
    ui->tableView_2->setModel(model1);
    ui->tableView_2->resizeColumnsToContents();


    QSqlQueryModel *model2 = new QSqlQueryModel (ui->tableView_3);
    model2->setQuery ("SELECT Persona.vards AS Vārds, Persona.uzvards AS Uzvārds, Kontaktinformacija.dzimsanas_datums AS Dzimšanas_datums "
                      "FROM Kontaktinformacija JOIN Persona ON Kontaktinformacija.ID_persona = Persona.ID "
                      "order by strftime('%m', Kontaktinformacija.dzimsanas_datums), strftime('%d', Kontaktinformacija.dzimsanas_datums)");
    ui->tableView_3->setModel(model2);
    ui->tableView_3->resizeColumnsToContents();
}

void skatit_pers::on_pushButton_clicked()
{
    QVector<QString> vu;
    vu=mw.db.vardsuzvards();
    ui->comboBox->clear();
    for (int i=0; i<vu.size(); i++){
        ui->comboBox->addItem(vu[i]);
    }

}


void skatit_pers::on_ieladet_clicked()
{
    QVector<QDate> datumi;
    QVector<int> darbibas;
    QVector<QTime> laiki;
    double kopejais_dienas_laiks=0;
    double kopejais_perioda_laiks=0;
    vector<double> kopejais_laiks;

    bool q=true;

    QDate sakums= ui->sak_dat->date();
    QDate beigas= ui->beig_dat->date();

    int ID =ui->personas->currentIndex();
    int personas_ID=ID1[ID];

    mw.db.iegut_apmeklejumus(personas_ID, datumi, darbibas, laiki, sakums, beigas);
if (datumi.size()==0) QMessageBox::information(this,tr(" "), tr("Personai nav neviena ieraksta šajā laika posmā"));
else{
    QTime ped_laiks;
    QDate datums;
    QVector <QDate> datumi1;
    QVector <QTime> sak_laik;
    QVector <QTime>beig_laik;
    int a=0;

    if (laiki.size()>0) {
    ped_laiks=laiki[0];
    sak_laik.push_back(laiki[0]);
    datums=datumi[0];
    datumi1.push_back(datums);
        }

    if (datumi.size()>1){
        for(a=1; a<datumi.size(); a++){
            if (datums!=datumi[a]){
                q=false;
                datums=datumi[a];
                datumi1.push_back(datums);
                kopejais_laiks.push_back(kopejais_dienas_laiks/3600);//dala ar 3600, lai iegūtu stundu skaitu
                kopejais_dienas_laiks=0;
                sak_laik.push_back(laiki[a]);
                beig_laik.push_back(laiki[a-1]);
            }

            if(darbibas[a]==0){
            ped_laiks=laiki[a];
            q=true;
         }
            //lai iegūtu kopējo laiku periodā
            if((darbibas[a]==1) && (q==true)){
                double starpiba= ped_laiks.secsTo(laiki[a]);
                kopejais_dienas_laiks=kopejais_dienas_laiks+starpiba;
                q=false;
            }
       }
        kopejais_laiks.push_back(kopejais_dienas_laiks/3600);

    }
if(laiki.size()>0){
    int size=laiki.size();
    beig_laik.push_back(laiki[size-1]);}

QStandardItemModel *model = new QStandardItemModel(this);


QStringList nosaukumi = { "Datums", "Pirmās darbības laiks", "Pēdējās darbības laiks", "Pavadītais laiks darbavietā(h)" };
model->setHorizontalHeaderLabels(nosaukumi);


for (int row = 0; row < datumi1.size(); ++row) {
    for (int column = 0; column < 4; ++column) {
        if(column==0) {
             QString dateString = datumi1[row].toString("dddd d.MM.yyyy");
             QStandardItem *item = new QStandardItem(dateString);
             model->setItem(row, column, item);}

        if(column==1) {
             QString timString = sak_laik[row].toString();
             QStandardItem *item = new QStandardItem(timString);
             model->setItem(row, column, item);}

        if(column==2) {
            QString timsString = beig_laik[row].toString();
            QStandardItem *item = new QStandardItem(timsString);
            model->setItem(row, column, item);}

        if(column==3) {
            //double val = 1.2;
            QString str= QString::number(kopejais_laiks[row], 'f', 2);
            //QString timsString = QString::number(kopejais_laiks[row]);
            QStandardItem *item = new QStandardItem(str);
            model->setItem(row, column, item);}
    }

}

ui->tableView_4->setModel(model);
ui->tableView_4->resizeColumnsToContents();

for(unsigned long a=0; a<kopejais_laiks.size();a++){
    kopejais_perioda_laiks=kopejais_perioda_laiks+ kopejais_laiks[a];
}
    QString str= QString::number(kopejais_perioda_laiks, 'f', 2);
    ui->viss->setStyleSheet("font: 16pt;");
    ui->viss->setText(str);

}
}

//parāda personas izvēles logā
void skatit_pers::paradit_personas(){

        QVector<QString> vardiuzvardi;
        vardiuzvardi=mw.db.vardsuzvards1(ID1);
        ui->personas->clear();
        for (int i=0; i<vardiuzvardi.size(); i++){
            ui->personas->addItem(vardiuzvardi[i]);
    }

}

skatit_pers::~skatit_pers()
{
    delete ui;
}
