#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QComboBox>
#include <QGridLayout>
#include <QStringList>
#include <QDebug>
#include <QString>
#include <QMessageBox>



namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    bool ir=false;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void p();

private:
    Ui::Login *ui;
    QString lietotajvards = "Admin";
    QString parole = "test";


};

#endif // LOGIN_H
