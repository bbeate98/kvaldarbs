#include "mainwindow.h"
#include <QApplication>
#include "login.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.trenet();
    w.show();

    return a.exec();

}
