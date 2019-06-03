#ifndef SKATIT_PERS_H
#define SKATIT_PERS_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class skatit_pers;
}

class skatit_pers : public QDialog
{
    Q_OBJECT

public:
    explicit skatit_pers(QWidget *parent = nullptr);
    ~skatit_pers();


private slots:
    void on_pushButton_clicked();

    void on_ieladet_clicked();

private:
    Ui::skatit_pers *ui;
    MainWindow mw;
    void paradit_personas();
    void paradit();
    QVector<int>ID1;
};

#endif // SKATIT_PERS_H
