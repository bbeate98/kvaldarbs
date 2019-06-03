#ifndef PIEVIENOT_LIGUMS_H
#define PIEVIENOT_LIGUMS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class pievienot_ligums;
}

class pievienot_ligums : public QDialog
{
    Q_OBJECT

public:
    explicit pievienot_ligums(QWidget *parent = nullptr);
    ~pievienot_ligums();

private slots:
    void on_pievienot_lig_clicked();

private:
    Ui::pievienot_ligums *ui;
    MainWindow mw;
};

#endif // PIEVIENOT_LIGUMS_H
