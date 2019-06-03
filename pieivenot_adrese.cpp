#include "pieivenot_adrese.h"
#include "ui_pieivenot_adrese.h"
#include "QMessageBox"


pieivenot_adrese::pieivenot_adrese(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pieivenot_adrese)
{
    ui->setupUi(this);
}

pieivenot_adrese::~pieivenot_adrese()
{
    delete ui;
}
//pievieno adresi datubāzei
void pieivenot_adrese::on_pievienot_adrese_clicked()
{
    QString iela=ui->iela->text();
    QString num=ui->mag_dzivokl_num->text();
    QString pilseta=ui->pilseta->text();
    QString indekss=ui->indekss->text();

   if ((iela.size()==0||num.size()==0)||(pilseta.size()==0)||(indekss.size()==0)) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
    else{
        QMessageBox::StandardButton reply;

        reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies pievienot šo adresi?"),
        QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {
           mw.db.pievienot_adresi(iela,num,pilseta,indekss);
            close();
        }

     if(reply == QMessageBox::Cancel)
     {
            close();
        }

    }
}
