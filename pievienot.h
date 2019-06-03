#ifndef PIEVIENOT_H
#define PIEVIENOT_H

#include <QDialog>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <vector>
#include <iostream>
#include <QMessageBox>
#include "pievienot_sak.h"


using namespace std;

namespace Ui {
class Pievienot;
}

class Pievienot : public QDialog
{
    Q_OBJECT

public:
    explicit Pievienot(QWidget *parent = nullptr);
    ~Pievienot();


private slots:
    void on_pushButton_clicked();


private:
    Ui::Pievienot *ui;
    //MainWindow mw;
    pievienot_sak piev;


};

#endif // PIEVIENOT_H
