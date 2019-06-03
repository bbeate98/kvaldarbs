#ifndef PIEVIENOT_PIEKL_H
#define PIEVIENOT_PIEKL_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class pievienot_piekl;
}

class pievienot_piekl : public QDialog
{
    Q_OBJECT

public:
    explicit pievienot_piekl(QWidget *parent = nullptr);
    ~pievienot_piekl();

private slots:
    void on_pievienot_clicked();

private:
    Ui::pievienot_piekl *ui;
    void paradit();
    MainWindow mw;
};

#endif // PIEVIENOT_PIEKL_H
