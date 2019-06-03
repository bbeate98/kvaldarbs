#ifndef PIEVIENOT_SAK_H
#define PIEVIENOT_SAK_H

#include <QDialog>

namespace Ui {
class pievienot_sak;
}

class pievienot_sak : public QDialog
{
    Q_OBJECT

public:
    explicit pievienot_sak(QWidget *parent = nullptr);
    ~pievienot_sak();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pievienot_piekluvi_clicked();

private:
    Ui::pievienot_sak *ui;
};

#endif // PIEVIENOT_SAK_H
