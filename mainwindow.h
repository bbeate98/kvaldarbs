#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include"opencv2/face.hpp"
using namespace cv;
#include "datubaze.h"
#include "pievienot.h"
#include "pievienot_sak.h"
#include <iostream>

using namespace std;
using namespace cv::face;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    Mat Y;
    Mat YA;
    datubaze db;
    Pievienot pi;
    int abc;
    void trenet();

public slots:

    void update_window();


    void slept();

    void paradit1();

private slots:
    void on_pushButton_open_webcam_clicked();

    void on_pushButton_close_webcam_clicked();

    void on_pievienot_cilveku_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_11_clicked();

    void on_pievienot_bildes_clicked();

private:
    Ui::MainWindow *ui;
    vector<int> labels;
    Ptr<FaceRecognizer> model =  createFisherFaceRecognizer();
    //Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
    QTimer *timer;
    VideoCapture cap;
    Mat frame;
    QImage qt_image;
    QImage seja;
    vector <Mat> sejas;
    QVector <int> ID1;
    void paradit();

};

#endif // MAINWINDOW_H
