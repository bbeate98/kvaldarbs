#include "pievienot_piekl.h"
#include "ui_pievienot_piekl.h"
#include "QMessageBox"

pievienot_piekl::pievienot_piekl(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pievienot_piekl)
{
    ui->setupUi(this);
    paradit();
}

pievienot_piekl::~pievienot_piekl()
{
    delete ui;
}
//funkcija, lai pievienotu jaunu piekļuvi datubāzei
void pievienot_piekl::on_pievienot_clicked()
{
    QVector<QString> lietotajvardi;
    lietotajvardi=mw.db.lietotajvards();
    QString lietotajvards=ui->lineEdit->text();
    int a=0;

    //pārbauda vai sistēmā jau nav lietotājs ar šādu lietotājvārdu
    for(int i=0; i<lietotajvardi.size();i++){
        if (lietotajvards==lietotajvardi[i])
            a=1;
    }

    //parāda dialoglodziņu, ka sistēmā jau ir tāds lietotājvārds
    if (a==1){
        QMessageBox::information(this,tr("Nederīgs lietotājvārds"), tr("Lietotājvārds aizņemts, ievadi citu lietotājvārdu"));
    }
    else {

        QString parole=ui->lineEdit_2->text();
        int persona=ui->pievienot_personas->currentIndex();
        int atlauja=ui->atlauja->currentIndex();

        QVector<QString> vardsuzvards;
        QVector<int> index;
        vardsuzvards=mw.db.vardsuzvards_irpies(index);
        int personas_id = index[persona];
        if ((lietotajvards.size()==0||parole.size()==0)) QMessageBox::information(this,tr(" "), tr("Nav korekti ievadīti dati"));
         else{
        QMessageBox::StandardButton reply;

            reply = QMessageBox::question(this, "Vai tiešām?",
                                         QString("Vai vēlies pievienot šo piekļuvi?"),
                                          QMessageBox::Ok | QMessageBox::Cancel);

            if (reply == QMessageBox::Ok) {
                mw.db.pievienot_piekluvi(lietotajvards,parole,personas_id, atlauja);
                close();
            }

            if(reply == QMessageBox::Cancel)
            {
                close();
            }
        }
    }


    //te vajadzēs funkcijai padot atauju un personas id datubāzei, vēl pārbaude

    paradit();
}

void pievienot_piekl::paradit(){
    QVector<QString> vardsuzvards;
    QVector<int> index;
    vardsuzvards=mw.db.vardsuzvards_irpies(index);
    ui->pievienot_personas->clear();
    for (int i=0; i<vardsuzvards.size(); i++){
        ui->pievienot_personas->addItem(vardsuzvards[i]);
    }
ui->atlauja->clear();
ui->atlauja->addItem("Administrators");
ui->atlauja->addItem("Vadītājs");
}
