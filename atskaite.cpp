#include "atskaite.h"
#include "ui_atskaite.h"
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include "mainwindow.h"

atskaite::atskaite(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::atskaite)
{
    ui->setupUi(this);
}

//https://stackoverflow.com/questions/2469186/resizing-qt-widgets-when-their-children-are-hidden
//https://doc.qt.io/archives/qq/qq21-datawidgetmapper.html

//https://stackoverflow.com/questions/33997358/security-how-to-show-hide-by-password-qgroupbox-in-qt-app
//sis par adminiem...

//tableView_2

void atskaite::paradit(){

    MainWindow mw;
    QSqlQueryModel *model = new QSqlQueryModel (ui->tableView);
    model->setQuery ("SELECT * FROM Persona");
    ui->tableView->setModel(model);

    QVector<QString> vu;
    vu=mw.db.vardsuzvards();
    ui->comboBox->clear();
    for (int i=0; i<vu.size(); i++){
        ui->comboBox->addItem(vu[i]);
    }

}


atskaite::~atskaite()
{
    delete ui;
}
