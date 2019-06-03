#include "pievienot_sak.h"
#include "ui_pievienot_sak.h"
#include "pievienot.h"
#include "pievienot_amatu.h"
#include "pievienot_ligums.h"
#include "pievienot_kontaktinfo.h"
#include "pieivenot_adrese.h"
#include "pievienot_piekl.h"

pievienot_sak::pievienot_sak(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::pievienot_sak)
{
    ui->setupUi(this);
}

pievienot_sak::~pievienot_sak()
{
    delete ui;
}

void pievienot_sak::on_pushButton_clicked()
{
    Pievienot piev;
    piev.setModal(true);
    piev.exec();
}

void pievienot_sak::on_pushButton_2_clicked()
{
    pieivenot_adrese adr;
    adr.setModal(true);
    adr.exec();
}

void pievienot_sak::on_pushButton_3_clicked()
{
    pievienot_ligums lig;
    lig.setModal(true);
    lig.exec();
}



void pievienot_sak::on_pushButton_4_clicked()
{
    pievienot_amatu piev;
    piev.setModal(true);
    piev.exec();
}

void pievienot_sak::on_pushButton_5_clicked()
{
    pievienot_kontaktinfo kont;
    kont.setModal(true);
    kont.exec();
}

void pievienot_sak::on_pievienot_piekluvi_clicked()
{
    pievienot_piekl piekl;
    piekl.setModal(true);
    piekl.exec();
}
