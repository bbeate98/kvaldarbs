#ifndef DZEST_H
#define DZEST_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class dzest;
}

class dzest : public QDialog
{
    Q_OBJECT

public:
    explicit dzest(QWidget *parent = nullptr);
    ~dzest();

private slots:
    void on_dzest_bildes_clicked();
    void on_dzest_personu_clicked();
    void on_dzest_adresi_clicked();
    void on_dzest_ligumu_clicked();
    void on_dzest_amatu_clicked();
    void on_dzest_piekluvi_clicked();

private:
    Ui::dzest *ui;
    MainWindow mw;
    void paradit_pers_bil();
    void paradit_personas();
    void paradit_adreses();
    void paradit_amatus();
    void paradit_ligumus();
    void paradit_piekluves();
    QVector<int> ID1;
    QVector<int> ID2;
    QVector<int> ID3;
    QVector<int> ID4;
    QVector<int> ID5;
    QVector<int> ID6;
};

#endif // DZEST_H
