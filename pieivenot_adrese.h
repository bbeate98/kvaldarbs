#ifndef PIEIVENOT_ADRESE_H
#define PIEIVENOT_ADRESE_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class pieivenot_adrese;
}

class pieivenot_adrese : public QDialog
{
    Q_OBJECT

public:
    explicit pieivenot_adrese(QWidget *parent = nullptr);
    ~pieivenot_adrese();

private slots:
    void on_pievienot_adrese_clicked();

private:
    Ui::pieivenot_adrese *ui;
    MainWindow mw;
};

#endif // PIEIVENOT_ADRESE_H
