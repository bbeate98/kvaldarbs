#ifndef REDIGET_H
#define REDIGET_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class rediget;
}

class rediget : public QDialog
{
    Q_OBJECT

public:
    explicit rediget(QWidget *parent = nullptr);
    ~rediget();

private slots:
    void on_pushButton_clicked();


    void on_red_vardu_clicked();

    void on_rediget_uzvardu_clicked();

    void on_rediget_telefona_nummuru_clicked();

    void on_rediget_dzimsanas_datumu_clicked();

    void on_rediget_amatu_clicked();

    void on_rediget_ligumu_clicked();

    void on_rediget_adresi_clicked();

private:
    Ui::rediget *ui;
    MainWindow mw;
    void paradit_personas();
    QVector<int> ID1;
    int personas_ID;

    QVector<int> ID2;
    QVector<int> ID3;
    QVector<int> ID4;
    void paradit_info();
};

#endif // REDIGET_H
