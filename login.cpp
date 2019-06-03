#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"

//https://www.qtcentre.org/threads/56486-Connecting-from-a-dialog-to-mainWindow

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    if((username==lietotajvards)&&(password==parole)){
    ir=true;
    MainWindow mw;
    mw.slept();

    this->hide();

    //p();
    //connect(scene,SIGNAL(onSceneClicked()),this,SLOT(elipsaOFF()));


    //connect(this, SIGNAL(signal()), mw, SLOT();
            //connect(timer, SIGNAL(timeout()), this, SLOT(mw.pushButton_close_webcam c);
//connect(&d, SIGNAL(enteredText(QString)), ui->label, SLOT(setText(QString)));
    //mw.ui->mw.pushButton_close_webcam->setVisible(false);



    //MainWindow mw;
    //mw.setModal(true);
    //mw.exec();
    //mw.show();
}
    else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, " ",
                                     QString("Nepareiza parole un/vai lietotājvārds"),
            QMessageBox::Ok | QMessageBox::Cancel);

        if (reply == QMessageBox::Ok) {


        }

        if(reply == QMessageBox::Cancel)
        {
            close();
        }
    }

}

void Login::p(){

      MainWindow* another_object = new MainWindow();
      another_object->on_pushButton_11_clicked();
      //another_object->anotherMethod();


}

void Login::on_pushButton_2_clicked()
{
    close();
}
