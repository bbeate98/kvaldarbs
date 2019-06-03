#ifndef PIEVIENOT_KONTAKTINFO_H
#define PIEVIENOT_KONTAKTINFO_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class pievienot_kontaktinfo;
}

class pievienot_kontaktinfo : public QDialog
{
    Q_OBJECT

public:
    explicit pievienot_kontaktinfo(QWidget *parent = nullptr);
    ~pievienot_kontaktinfo();

private slots:
    void on_pievienot_kontakt_clicked();

private:
    Ui::pievienot_kontaktinfo *ui;
    MainWindow mw;
    void personas();
    void amati();
    void ligumi();
    void adrese();
    QVector <int> index;
    QVector <int> index_2;
    QVector <int> index_3;
    QVector <int> index_4;
};

#endif // PIEVIENOT_KONTAKTINFO_H
