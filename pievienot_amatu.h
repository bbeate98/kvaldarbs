#ifndef PIEVIENOT_AMATU_H
#define PIEVIENOT_AMATU_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class pievienot_amatu;
}

class pievienot_amatu : public QDialog
{
    Q_OBJECT

public:
    explicit pievienot_amatu(QWidget *parent = nullptr);
    ~pievienot_amatu();

private slots:
    void on_pievienot_amats_clicked();

private:
    Ui::pievienot_amatu *ui;
    MainWindow mw;
};

#endif // PIEVIENOT_AMATU_H
