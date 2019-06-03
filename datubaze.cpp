#include "datubaze.h"
#include <iostream>
#include <string>
#include <QSqlQuery>
#include <QDebug>
#include <QBuffer>
#include <QDir>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "skatit_pers.h"
#include <QSqlTableModel>
#include <QVector>
#include "QMessageBox"

using namespace std;

datubaze::datubaze(){
  //pieslēdzas datu bāzei
    if(piesl==false){
        QSqlDatabase db;
         if (!db.open()){
         db = QSqlDatabase::addDatabase("QSQLITE");
         db.setDatabaseName("/home/bbeate/Desktop/new/Gui_istais/db.sqlite");
     }
          if (!db.open())
          {
              QMessageBox msgBox;
                  msgBox.setText("Nevar pieslēgties datu bāzei!");
                  msgBox.setWindowTitle(" ");
                  msgBox.exec();
        }

            piesl=true;
        }

    QSqlQuery query;
//izveido tabuas, ja tādas vēl neeksistē
    query.exec("PRAGMA foreign_keys = ON;");

    query.exec("create table Persona (ID INTEGER PRIMARY KEY AUTOINCREMENT, "
               "vards char(20), uzvards char(20), bildes int, irdarba int)");


    query.exec("create table Apmeklejums (ID_ap INTEGER PRIMARY KEY AUTOINCREMENT, "
               "laiks TIME DEFAULT (TIME('now','localtime')) NOT NULL, "
               "datums DATE DEFAULT (DATE('now','localtime')) NOT NULL, darbiba int NOT NULL,"
               " ID_pers int, FOREIGN KEY(`ID_pers`) REFERENCES `Persona`(`ID`))");


    query.exec("create table Ligums (ID_lig INTEGER PRIMARY KEY AUTOINCREMENT, "
               "lig_nummurs char(10) NOT NULL, nosl_datums DATE NOT NULL, slodze int NOT NULL, beigu_dat DATE)");


    query.exec("create table Adrese (ID_ad INTEGER PRIMARY KEY AUTOINCREMENT, "
               "iela char(50), majas_dzivokla_nummurs char(10), pilseta char(20), pasta_indekss char(8))");


    query.exec("create table Amats (ID_am INTEGER PRIMARY KEY AUTOINCREMENT, "
               "nosaukums char(20) NOT NULL, apraksts TEXT)");

    query.exec("create table Pieslegsanas (Lietotajvards char(20) NOT NULL, "
               "Parole char(20) NOT NULL, atlauja INTEGER NOT NULL, ID_pers INTEGER NOT NULL, FOREIGN KEY(`ID_pers`) REFERENCES `Persona`(`ID`) )");

    query.exec("create table Kontaktinformacija (ID_kon INTEGER PRIMARY KEY AUTOINCREMENT,"
               " Telefona_nr char(12), dzimsanas_datums DATE NOT NULL, `ID_persona`	INTEGER NOT NULL,"
               " `ID_amats`	INTEGER NOT NULL, `ID_ligums`	INTEGER NOT NULL, `ID_adrese`	INTEGER NOT NULL,"
               " FOREIGN KEY(`ID_adrese`) REFERENCES `Adrese`(`ID_ad`), FOREIGN KEY(`ID_persona`) REFERENCES `Persona`(`ID`),"
               " FOREIGN KEY(`ID_amats`) REFERENCES `Amats`(`ID_am`), FOREIGN KEY(`ID_ligums`) REFERENCES `Ligums`(`ID_lig`))");

}
//funkcija, lai aizvērtu datubāzes savienojumu, programmas aizvēršanas brīdī.
void datubaze::aizvert_datubazi(){

        {
            QSqlDatabase db = QSqlDatabase::database();
            db.close();
        }
        QSqlDatabase::removeDatabase( QSqlDatabase::defaultConnection );
        return;
}


void datubaze::apmeklejums(int id){
    QSqlQuery query;
    query.prepare("INSERT INTO Apmeklejums (ID_pers) "
                  "VALUES (?)");
    query.addBindValue(id);
    query.exec();
}

//funkcija tiek izsaukta tad, kad sistēma tike reģistrēts jauns aomeklējums
void datubaze::jauns_apmeklejums(int id, int darbiba){
    QSqlQuery query;
    query.prepare("INSERT INTO Apmeklejums (darbiba, ID_pers) VALUES(:valA, :valB)");
    query.bindValue(":valA", darbiba);
    query.bindValue(":valB", id);
    query.exec();

    if(darbiba==0){
    query.prepare("UPDATE Persona SET irdarba = 1 WHERE ID=?");
    query.addBindValue(id);
    query.exec();}

    if(darbiba==1){
    query.prepare("UPDATE Persona SET irdarba = 0 WHERE ID=?");
    query.addBindValue(id);
    query.exec();}


  }

//funkcija, kas pievieno jaunu kontaktinformāciju
void datubaze::pievienot_adresi(QString iela, QString nummurs, QString pilseta, QString pasts){
    QSqlQuery Query;
    Query.prepare("INSERT INTO Adrese (iela, majas_dzivokla_nummurs, pilseta, pasta_indekss ) VALUES(:valA, :valB, :valC, :valD)");
    Query.bindValue(":valA", iela);
    Query.bindValue(":valB", nummurs);
    Query.bindValue(":valC", pilseta);
    Query.bindValue(":valD", pasts);
    Query.exec();

}

//funkcija, kas pievieno jaunu kontaktinformāciju
void datubaze::pievienot_kontaktinfo(QString tel, QDate datums, int id_pers, int id_adrese, int id_amats, int id_ligums){

    QSqlQuery Query;
    Query.prepare("INSERT INTO Kontaktinformacija (Telefona_nr, dzimsanas_datums, ID_persona, ID_amats, ID_ligums, ID_adrese) VALUES(:valA, :valB, :valC, :valD, :valE, :valF)");
    Query.bindValue(":valA", tel);
    Query.bindValue(":valB", datums);
    Query.bindValue(":valC", id_pers);
    Query.bindValue(":valD", id_amats);
    Query.bindValue(":valE", id_ligums);
    Query.bindValue(":valF", id_adrese);
    Query.exec();
}

//funkcija, kas pievieno jaunu līgumu
void datubaze::pievienot_ligumu(QString nummurs, QDate sakums, int slodze, QDate beigas){
    QSqlQuery Query;
    Query.prepare("INSERT INTO Ligums (lig_nummurs, nosl_datums, slodze, beigu_dat) VALUES(:valA, :valB, :valC, :valD)");
    Query.bindValue(":valA", nummurs);
    Query.bindValue(":valB", sakums);
    Query.bindValue(":valC", slodze);
    Query.bindValue(":valD", beigas);
    Query.exec();
}

//funkcija, kas pievieno padoto jauno amatu un tā aprakstu
void datubaze::pievienot_amatu(QString nosaukums, QString apraksts){
    QSqlQuery Query;
    Query.prepare("INSERT INTO Amats (nosaukums, apraksts) VALUES(:valA, :valB)");
    Query.bindValue(":valA", nosaukums);
    Query.bindValue(":valB", apraksts);
    Query.exec();
}

void datubaze::pievienot_piekluvi(QString lietotajvards, QString parole, int ID, int atlauja){
 QSqlQuery Query;
 int atlauja1=atlauja+1;
 Query.prepare("Insert into Pieslegsanas (Lietotajvards, Parole, ID_pers, atlauja) VALUES(:valA, :valB, :valC, :valD)");
 Query.bindValue(":valA", lietotajvards);
 Query.bindValue(":valB", parole);
 Query.bindValue(":valC", ID);
 Query.bindValue(":valD", atlauja1);
 Query.exec();
}

void datubaze::paradit_visus(){
     QSqlQuery query;
     query.prepare("SELECT * from Persona");
     query.exec();
}

void datubaze::pievienot_cilveku(QString vards, QString uzvards){
    QSqlQuery Query;
    Query.prepare("INSERT INTO Persona(vards, uzvards, bildes, irdarba) VALUES(:valA, :valB, 0, 0)");
    Query.bindValue(":valA", vards);
    Query.bindValue(":valB", uzvards);
    Query.exec();
}


void datubaze::rediget_vardu(int id, QString vards){
    QSqlQuery Query;
    Query.prepare("UPDATE Persona SET vards =:valA WHERE ID =:valB");
    Query.bindValue(":valA", vards);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_uzvardu(int id, QString uzvards){
    QSqlQuery Query;
    Query.prepare("UPDATE Persona SET uzvards = :valA WHERE ID = :valB");
    Query.bindValue(":valA", uzvards);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_telefons(int id, QString telefons){
    QSqlQuery Query;
    Query.prepare("UPDATE Kontaktinformacija SET Telefona_nr = :valA WHERE ID_persona = :valB");
    Query.bindValue(":valA", telefons);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_dzimsanas_datumu(int id, QDate dzimsanas_datums){
    QSqlQuery Query;
    Query.prepare("UPDATE Kontaktinformacija SET dzimsanas_datums = :valA WHERE ID_persona = :valB");
    Query.bindValue(":valA", dzimsanas_datums);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_amatu(int id, int amats){
    QSqlQuery Query;
    Query.prepare("UPDATE Kontaktinformacija SET ID_amats = :valA WHERE ID_persona = :valB");
    //UPDATE Kontaktinformacija SET ID_amats = 1 WHERE ID_persona = 1
    Query.bindValue(":valA", amats);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_ligumu(int id, int ligums){
    QSqlQuery Query;
    Query.prepare("UPDATE Kontaktinformacija SET ID_ligums = :valA WHERE ID_persona = :valB");
    Query.bindValue(":valA", ligums);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::rediget_adresi(int id, int adrese){
    QSqlQuery Query;
    Query.prepare("UPDATE Kontaktinformacija SET ID_adrese = :valA WHERE ID_persona = :valB");
    Query.bindValue(":valA", adrese);
    Query.bindValue(":valB", id);
    Query.exec();
}

void datubaze::iegut_vard_uzvardu(int id, QString &vards, QString &uzvards){
    QSqlQuery query;
    query.prepare("Select vards FROM Persona where ID = ?");
    query.addBindValue(id);
    query.exec();
    query.next();
    vards=query.value(0).toString();

    query.exec();
    query.prepare("Select uzvards FROM Persona where ID = ?");
    query.addBindValue(id);
    query.exec();
    query.next();
    uzvards=query.value(0).toString();
    query.exec();

}

QVector<QString> datubaze::pieejas(QVector<QString> &parole){
    QVector<QString> lietotajvardi;
    //šeit mēs iegūsim pieejas cilvēkim ar 1 pieeju(jeb administraoriem)
    QSqlQuery query;
    query.prepare("Select Lietotajvards, Parole  FROM Pieslegsanas where atlauja=1");
    query.exec();
    while( query.next() )
    {
        QString lietotajvards=query.value(0).toString();
        QString parol=query.value(1).toString();
        lietotajvardi.push_back(lietotajvards);
        parole.push_back((parol));
    }

return lietotajvardi;
}

QVector<QString> datubaze::pieejas2(QVector<QString> &parole){
    QVector<QString> lietotajvardi;
    //šeit mēs iegūsim pieejas cilvēkim ar 2 pieeju(jeb vadītājiem)
    QSqlQuery query;
    query.prepare("Select Lietotajvards, Parole  FROM Pieslegsanas where atlauja=2");
    query.exec();
    while( query.next() )
    {
        QString lietotajvards=query.value(0).toString();
        QString parol=query.value(1).toString();
        lietotajvardi.push_back(lietotajvards);
        parole.push_back((parol));
    }

return lietotajvardi;
}

void datubaze::dzest_adresi(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Adrese Where ID_ad= ?");
    query.addBindValue(id);
    query.exec();
}

void datubaze::dzest_ligumu(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Ligums Where ID_lig= ?");
    query.addBindValue(id);
    query.exec();
}

void datubaze::dzest_amatu(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Amats Where ID_am= ?");
    query.addBindValue(id);
    query.exec();
}

void datubaze::dzest_piekluvi(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Pieslegsanas Where ID_pers= ?");
    query.addBindValue(id);
    query.exec();
}

void datubaze::dzest_bildes(int id){
    QSqlQuery query;
    query.prepare("Select bildes FROM Persona where ID = ?");
    query.addBindValue(id);
    query.exec();
    query.next();
    int status = query.value(0).toInt();
    if (status==1){

        QString s1 = "/home/bbeate/Desktop/new/Gui_istais/bildes/";
        QString s2 = "/";
        QString s3 = QString::number(id);
        QString s4 = s1 + s2 + s3;

        QDir dir(s4);
        dir.removeRecursively();
        query.prepare("UPDATE Persona SET bildes = 0 WHERE ID=?");
        query.addBindValue(id);
        query.exec();


    }
    QMessageBox msgBox;
        msgBox.setText("Šajai personai nav pievienotas bildes");
        msgBox.setWindowTitle(" ");
        msgBox.exec();
}


void datubaze::dzest(int id){
    QSqlQuery query;
    query.prepare("DELETE FROM Persona WHERE ID = ?");
    query.addBindValue(id);
    query.exec();
    query.prepare("SELECT ID_ligums from Kontaktinformacija WHERE Kontaktinformacija.ID_persona= ?");
    query.exec();
    int ID_lig = query.value(0).toInt();
    query.prepare("DELETE FROM Ligums WHERE ID = ?");
    query.addBindValue(ID_lig);
    query.exec();
    query.prepare("Delete FROM Apmeklejums WHERE Apmeklejums.ID_pers = ?");
    query.addBindValue(id);
    query.exec();
    query.exec("Delete FROM Pieslegsanas WHERE Pieslegsanas.ID_pers= ?");
    query.addBindValue(id);
    query.exec();
}



void datubaze::pievienot_bildes(int a, vector<cv::Mat> bildes){

      QSqlQuery query;
      query.prepare("Select bildes FROM Persona where ID = ?");
      query.addBindValue(a);
      query.exec();
      query.next();
      int status = query.value(0).toInt();
      if (status==0){

          QString s1 = "/home/bbeate/Desktop/new/Gui_istais/bildes/";
          QString s2 = "/";
          QString s3 = QString::number(a);
          QString s4 = s1 + s2 + s3;

          QDir dir(s4);
          if (!dir.exists())
              dir.mkpath(".");

          for(unsigned long i=0 ;i<bildes.size();i++ )
            {
              stringstream ss;
              string name = "/home/bbeate/Desktop/new/Gui_istais/bildes/";
              string apaks = "_";
              string slash = "/";
              string form = ".jpg";
              ss<<name<<a<<slash<<a<<apaks<<i<<form;
              string filename = ss.str();
              imwrite(filename, bildes[i]);
          }
          query.prepare("UPDATE Persona SET bildes = 1 WHERE ID=?");
          query.addBindValue(a);
          query.exec();

      }
}

void datubaze::dzest_personas_bildes(int id){
    QSqlQuery query;
    query.prepare("Select bildes FROM Persona where ID = ?");
    query.addBindValue(id);
    query.exec();
    query.next();
    int status = query.value(0).toInt();
    cout<<endl<<id<<endl;
    if (status==1){

        QString s1 = "/home/bbeate/Desktop/new/Gui_istais/bildes/";
        QString s2 = "/";
        QString s3 = QString::number(id);
        QString s4 = s1 + s2 + s3;

        QDir dir(s4);
        dir.removeRecursively();//izdzēš mapīti ar bildēm

        query.prepare("UPDATE Persona SET bildes = 0 WHERE ID=?");
        query.addBindValue(id);
        query.exec();

    }
}



void rediget_personas_datus(int id){

    QSqlQuery query;
    query.prepare("INSERT INTO Apmeklejums (ID_pers int) "
                  "VALUES (?)");
    query.addBindValue(id);
    query.exec();
}

vector<int> datubaze::iegut_nummurus(){
    vector<int> nummuri;
    QSqlQuery query;
    query.prepare("SELECT * FROM Persona");
    query.exec();
         while( query.next() )
         {
             int f = query.value( 0 ).toInt();
             nummuri.push_back(f);
         }

return nummuri;
}

vector<cv::Mat> datubaze::iegut_bildes(vector<int> &nummuri){

     QSqlQuery query;
     vector<cv::Mat> bil;

     query.prepare("SELECT ID FROM Persona WHERE bildes=1"); //saglabā int vektorā tās ID vertības, kam ir bildes.
     query.exec();
     while( query.next() )
     {
         int f = query.value(0).toInt();
         nummuri.push_back(f);
     }

     for (unsigned long s=0; s<nummuri.size();s++){
         for (int r=0; r<10;r++){
             stringstream ss;
             string name = "/home/bbeate/Desktop/new/Gui_istais/bildes/";
             string apaks = "_";
             string slash = "/";
             string form = ".jpg";
             ss<<name<<nummuri[s]<<slash<<nummuri[s]<<apaks<<r<<form;
             string filename = ss.str();
             cv::Mat I = cv::imread(filename, 0);
             bil.push_back(I);

                      }
     }

      return bil;
}



vector<cv::Mat> datubaze::apskatit_pers_bildes(int d){
    vector<cv::Mat> bildes;
    d=d+1;
    return bildes;
}

QVector<QString> datubaze::vardsuzvards(){
    QVector<QString> vu;

        QSqlQuery query;
        query.prepare("Select vards,uzvards FROM Persona");
        query.exec();
        while( query.next() )
        {
            QString vards=query.value(0).toString();
            QString uzvards=query.value(1).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
        }

return vu;
}

QVector<QString> datubaze::vardsuzvards1(QVector<int> &index){
    QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select ID,vards,uzvards FROM Persona");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString vards=query.value(1).toString();
            QString uzvards=query.value(2).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
            index.push_back(status);
        }
return vu;

}

QVector<QString> datubaze::vardsuzvards_irbildes(QVector<int> &index){
    QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select ID,vards,uzvards FROM Persona WHERE bildes=1");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString vards=query.value(1).toString();
            QString uzvards=query.value(2).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::vardsuzvards_navbildes(QVector<int> &index){
    QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select ID,vards,uzvards FROM Persona WHERE bildes=0");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString vards=query.value(1).toString();
            QString uzvards=query.value(2).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::neizmantotas_adreses(QVector<int> &index){
    QVector<QString> nezadre;
    QSqlQuery query;
    query.prepare("Select DISTINCT Adrese.ID_ad, Adrese.iela, Adrese.majas_dzivokla_nummurs, Adrese.pilseta, "
                  "Adrese.pasta_indekss From Adrese Left Join Kontaktinformacija ON Adrese.ID_ad=Kontaktinformacija.ID_adrese "
                  "Where Kontaktinformacija.ID_adrese IS NULL");
    query.exec();
    while( query.next() )
    {
        int status = query.value(0).toInt();
        QString iela=query.value(1).toString();
        QString num=query.value(2).toString();
        QString pilseta=query.value(3).toString();
        QString pasts=query.value(4).toString();

        QString result = iela + " " + num + ", "+ pilseta + ", "+ pasts;
        nezadre.push_back(result);//pieliek jaunu adresi
        index.push_back(status);//pieliek adreses ID no datubāzes
    }

return nezadre; //atgriež vektoru ar pilnajiem adrešu nosaukumiem
}

QVector<QString> datubaze::neizmantotie_ligumi(QVector<int> &index){

        QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select DISTINCT Ligums.ID_lig, Ligums.lig_nummurs From Ligums Left Join Kontaktinformacija "
                      "ON Ligums.ID_lig=Kontaktinformacija.ID_ligums Where Kontaktinformacija.ID_ligums IS NULL");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString num =query.value(1).toString();
            vu.push_back(num);
            index.push_back(status);
        }
    return vu;
}

QVector<QString> datubaze::piekluves(QVector<int> &index){
    QVector<QString> vu;
    QSqlQuery query;
    query.prepare("Select Persona.ID, Persona.vards, Persona.uzvards, Pieslegsanas.atlauja From Persona "
                  "Join Pieslegsanas ON Persona.ID=Pieslegsanas.ID_pers ");
    query.exec();
    while( query.next() )
    {
        int status = query.value(0).toInt();
        QString vards =query.value(1).toString();
        QString uzvards =query.value(2).toString();
        int atlauj = query.value(3).toInt();
        QString nosauk;
        if (atlauj==1){
            nosauk="administrators";
        }
        else {
            nosauk="vadītājs";
        }
        QString result = vards + " " + uzvards + ", "+ nosauk;
        vu.push_back(result);
        index.push_back(status);
    }
return vu;
}

QVector<QString> datubaze::neizmantotie_amati(QVector<int> &index){
    QVector<QString> vu;
    QSqlQuery query;
    query.prepare("Select DISTINCT Amats.ID_am, Amats.nosaukums From Amats Left Join Kontaktinformacija "
                  "ON Amats.ID_am=Kontaktinformacija.ID_amats Where Kontaktinformacija.ID_amats IS NULL");
    query.exec();
    while( query.next() )
    {
        int status = query.value(0).toInt();
        QString num =query.value(1).toString();
        vu.push_back(num);
        index.push_back(status);
    }
return vu;

}

QVector<QString> datubaze::vardsuzvards_kinfo(QVector <int> &index){
    QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select DISTINCT Persona.ID, Persona.vards, Persona.uzvards From Persona "
                      "Left Join Kontaktinformacija ON Persona.ID=Kontaktinformacija.ID_persona Where Kontaktinformacija.ID_persona IS NULL");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString vards=query.value(1).toString();
            QString uzvards=query.value(2).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::vardsuzvards_irpies(QVector<int> &index){
    QVector<QString> vu;
        QSqlQuery query;
        query.prepare("Select DISTINCT Persona.ID, Persona.vards, Persona.uzvards From Persona "
                      "Left Join Pieslegsanas ON Persona.ID=Pieslegsanas.ID_pers Where Pieslegsanas.ID_pers IS NULL");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString vards=query.value(1).toString();
            QString uzvards=query.value(2).toString();

            QString result = vards + " " + uzvards;
            vu.push_back(result);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::lietotajvards(){
    QSqlQuery query;
    query.prepare("Select Lietotajvards FROM Pieslegsanas");
    query.exec();
    QVector<QString> lietotaj;
    while( query.next() )
    {
        QString vards=query.value(0).toString();
        lietotaj.push_back(vards);
    }
    return lietotaj;
}





QVector<QString> datubaze::amati(QVector <int> &index){
    QVector<QString> vu;

        QSqlQuery query;
        query.prepare("Select ID_am,nosaukums FROM Amats");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString amats=query.value(1).toString();
            vu.push_back(amats);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::ligumi(QVector <int> &index){
    QVector<QString> vu;

        QSqlQuery query;
        query.prepare("Select DISTINCT Ligums.ID_lig, Ligums.lig_nummurs From Ligums "
                      "Left Join Kontaktinformacija ON Ligums.ID_lig=Kontaktinformacija.ID_ligums Where Kontaktinformacija.ID_ligums IS NULL");
        query.exec();
        while( query.next() )
        {
            int status = query.value(0).toInt();
            QString ligums=query.value(1).toString();
            vu.push_back(ligums);
            index.push_back(status);
        }
return vu;
}

QVector<QString> datubaze::adrese(QVector <int> &index){
    QVector<QString> vu;
    QSqlQuery query;
    query.prepare("Select ID_ad,iela,majas_dzivokla_nummurs, pilseta, pasta_indekss FROM Adrese");
    query.exec();
    while( query.next() )
    {
        int status = query.value(0).toInt();
        QString iela=query.value(1).toString();
        QString num=query.value(2).toString();
        QString pils=query.value(3).toString();
        QString pasta_in=query.value(4).toString();
        QString result = iela + " " + num + ", " + pils + ", "+pasta_in;
        vu.push_back(result);
        index.push_back(status);
    }

return vu;
}

void datubaze::visi_dati(int ID, QString &vards, QString &uzvards, QString &tel_nr, QString &amats, QString &ligums, QDate &dz_dat, QString &adrese){
    QSqlQuery query;
    query.prepare("Select vards from Persona WHERE ID= ?");
    query.addBindValue(ID);
    query.exec();
    if(query.next()){
        vards=query.value(0).toString();
    }


    query.prepare("Select uzvards from Persona WHERE ID= ?");
    query.addBindValue(ID);
    query.exec();
    if(query.next())     uzvards=query.value(0).toString();

    query.prepare("Select Telefona_nr from Kontaktinformacija WHERE ID_persona= ?");
    query.addBindValue(ID);
    query.exec();

    if(query.next())    tel_nr=query.value(0).toString();

     query.prepare("Select dzimsanas_datums from Kontaktinformacija WHERE ID_persona= ?");
     query.addBindValue(ID);
     query.exec();
     if(query.next())
     dz_dat=query.value(0).toDate();

     query.prepare("Select Amats.nosaukums From Amats Join Kontaktinformacija ON Amats.ID_am=Kontaktinformacija.ID_amats Where Kontaktinformacija.ID_persona= ?");
     query.addBindValue(ID);
     query.exec();
     if(query.next())
     amats=query.value(0).toString();

     query.prepare("Select Ligums.lig_nummurs From Ligums Join Kontaktinformacija ON Ligums.ID_lig=Kontaktinformacija.ID_ligums Where Kontaktinformacija.ID_persona= ?");
     query.addBindValue(ID);
     query.exec();
     if(query.next())
     ligums=query.value(0).toString();

     query.prepare("Select Adrese.iela, Adrese.majas_dzivokla_nummurs, Adrese.pilseta, Adrese.pasta_indekss From Adrese "
                   "Join Kontaktinformacija ON Adrese.ID_ad=Kontaktinformacija.ID_adrese "
                   "Where Kontaktinformacija.ID_persona=?");
     query.addBindValue(ID);
     query.exec();
     if(query.next()){
         QString iela=query.value(0).toString();
         QString num=query.value(1).toString();
         QString pilseta=query.value(2).toString();
         QString pasts=query.value(3).toString();
         adrese= iela + " " + num + ", "+ pilseta + ", "+ pasts;}

}

void datubaze::iegut_apmeklejumus(int a, QVector<QDate> &datumi, QVector<int> &darbibas, QVector<QTime> &laiki, QDate sakums, QDate beigas){
    QSqlQuery query;
    query.prepare("SELECT datums, laiks, darbiba from Apmeklejums where datums >= ? and datums <= ? AND ID_pers = ?");
    query.addBindValue(sakums);
    query.addBindValue(beigas);
    query.addBindValue(a);
    query.exec();

    query.exec();

    while( query.next() )
    {
        QDate datums=query.value(0).toDate();
        QTime laiks=query.value(1).toTime();
        int darbiba=query.value(2).toInt();

        datumi.push_back(datums);
        laiki.push_back(laiks);
        darbibas.push_back(darbiba);
    }
}

datubaze::~datubaze(){
   //Destruktors

}

