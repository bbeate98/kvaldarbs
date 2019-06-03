#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pievienot.h"
#include "datubaze.h"
#include "skatit_pers.h"
#include "rediget.h"
#include <QDialog>
#include <QMessageBox>
#include "dzest.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    slept();

    timer = new QTimer(this);
    ui->label_6->setVisible(false);
    paradit();

}

MainWindow::~MainWindow()
{
    delete ui;
    db.aizvert_datubazi();
}

void MainWindow::on_pushButton_open_webcam_clicked()
{
    cap.open(0);

    if(!cap.isOpened())  // pārbauda vai kamera ir atvērta
    {
        QMessageBox::information(this,tr(" "), tr("Nevar atvērt kameru"));
    }
    else
    {
        connect(timer, SIGNAL(timeout()), this, SLOT(update_window())); //sakonektē taimeri ar fnkciju update_window, jeb funkciju, kas iegūšt jaunu kadru
        timer->start(20);
    }
}

void MainWindow::on_pushButton_close_webcam_clicked()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));//signālu atslēdz, tādējādi kamera izslēdzas
    cap.release();

    Mat image = Mat::zeros(frame.size(),CV_8UC3);
    qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::update_window()
{
    cap >> frame; //iegūst kadru

    CascadeClassifier cascade;
    cascade.load( "/home/bbeate/Desktop/new/Gui_istais/haarcascade_frontalface_default.xml" ) ; //kaskāde, kas ierauga kadrā cilvēku sejas

    vector<Rect> faces;//vektora ar atpazītajām sejām
    Mat gray, smallImg, cropped_Img;
    cvtColor( frame, gray, COLOR_BGR2GRAY ); // Convert to Gray Scale
    double scale=1;
    double fx = 1 / scale;


    // samazina pelēktoņu bildi
    cv::resize( gray, smallImg, Size(), fx, fx, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    // atrod sejas izmantojot iepriekš minēto kaskādi
    cascade.detectMultiScale( smallImg, faces, 1.1,
                            2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    Mat beate = frame.clone();//noklonē kadru, lai pēc tam to varētu izmantot


        if (faces.size()>0)
    {
        Rect r = faces[0];
        Mat smallImgROI;
        vector<Rect> nestedObjects;


        Scalar color = Scalar(255, 0, 0); // Krāsa sejas apvilkšanai, kas šajā gadījumā ir zila
        rectangle( frame, cvPoint(cvRound(r.x*scale), cvRound(r.y*scale)),
                    cvPoint(cvRound((r.x + r.width-1)*scale),
                    cvRound((r.y + r.height-1)*scale)), color, 3, 8, 0);//apvelk zilu četrstūri apkārt sejai

        int x, y, width, height;
        x=(r.x);
        y=(r.y);
        width=(r.width);
        height=(r.height);
        //pārbauda vai ir iegūts pozitīva izmēra sejas attēls, ja jā, tas seju izgriez un uzglabā mainīgajā Y
        if((x>0)&& (width>0) &&(height>0) && (y>0)){

            beate(Rect(x, y, width, height)).copyTo(Y);
            cv::resize(Y, Y, Size(100, 110));
            cvtColor(Y, Y, CV_BGR2RGB);


    }
        smallImgROI = smallImg( r );
        Rect myROI(10, 10, 100, 100);
    }

    cvtColor(frame, frame, CV_BGR2RGB);//pārvērš krāsu


         seja = QImage((const unsigned char*) (Y.data), Y.cols, Y.rows, QImage::Format_RGB888);//attēlo sejas attēlu blakus lielajam kadram
         ui->label_2->setPixmap(QPixmap::fromImage(seja));
         ui->label_2->resize(ui->label_2->pixmap()->size());
         ui->label_6->setVisible(true);


    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);//attēlo kameras kadru ar apvilkto seju

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}


void MainWindow::on_pievienot_cilveku_clicked()
{
    pievienot_sak pievienot;
    pievienot.setModal(true);
    pievienot.exec();
}

void MainWindow::on_pushButton_clicked()
{
    sejas.clear();
    unsigned long a;
    a=sejas.size();
    int value = static_cast<int>(a);
    ui->progressBar->setValue(value);
}

//funkcija personas sejas uzņemšanai
void MainWindow::on_pushButton_2_clicked()
{
    if(!cap.isOpened())
    {
        QMessageBox::information(this,tr(" "), tr("Nevar uzņemt bildes, kamera nav atvērta"));
    }
    else{
    bool q=false;
    cv::Mat YY;
    if (Y.empty()){q=true; }
    if(q==false) {  cv::cvtColor(Y, YY, CV_BGR2GRAY);}


    if ((sejas.size()<10&&(q==false))){
            sejas.push_back(YY);
                if(sejas.size()==10)
                QMessageBox::information(this,tr(" "), tr("10 sejas ir saglabātas vektorā, spied pogu, lai pievienotu šīs bildes pie kādas personas"));
           }

    unsigned long a;
    a=sejas.size();
    int value = static_cast<int>(a);
    ui->progressBar->setValue(value);
  }
}

//funkcija kas trene sejas atpazīšanas modeli
void MainWindow::trenet(){
    vector<Mat> bildes;//Vectors, kurā glabāsies visas bilde, kuras trennēs
    vector<int> nummuri;//Int vektors, kurā glabāsies visi ID, kurām personām ir bildes
    bildes=db.iegut_bildes(nummuri);//No datubāzesiegūst bildes un personu ID
    if(bildes.size()<20)
        QMessageBox::information(this,tr(" "), tr("Nevar veikt atpazīšanas trenēšanu, jo nav vismaz 2 cilvēki ar 10 bildēm"));
        else {
            if(labels.empty()){
                unsigned long g=0; //veido katrai bildei atbilstošo ID
                for (unsigned long a=0; a<nummuri.size(); a++) {
                    for (unsigned long b=0; b<10;b++){
                        labels.push_back(nummuri[g]);
                        }
                g++;
                }
              model->train(bildes, labels); //tiek trennēts "Fisherface recognizer" modelis
           }
        }
}

void MainWindow::on_pushButton_6_clicked()
{
    trenet();//izsauc funkciju trenet

  }

//funkcija, kas pareģo, kura persona ir attēlā redzamā persona
void MainWindow::on_pushButton_7_clicked()
{
    bool q=false; //izveidots mainīgais, lai varētu veikt pārbaudi, vai nav padota atpazīšanai tukša bildes
    cv::Mat YY;
    if (Y.empty()){q=true; }
    if(q==false) {  cv::cvtColor(Y, YY, CV_BGR2GRAY);} //ja bilde nav tukša, tad to pārveido pelēktoņos
    int predicted_label = -1;
    double predicted_confidence = 0.0;
    model->predict(YY, predicted_label, predicted_confidence); //funkcija, kas atrod atbilstošo personu, uzņēmtajai sejai
    QVector<QString> vu;
    vu=db.vardsuzvards(); //iegūst vārdus un uzvārdus no datubāzes, lai varētu pārjautāt darbiniekam, vai tas tiešām ir viņš
    vector<int> nummuri;
    nummuri=db.iegut_nummurus();//iegūšt atbilstošos ID
    int a=0;
    for(unsigned long e=0; e<nummuri.size();e++){
      if  (predicted_label==nummuri[e]){
            a=e;
            break;
        }
    }

    QMessageBox msgBox; //tiek izveidots dialoglodziņš
    msgBox.setWindowTitle(" ");
    msgBox.setText(tr("Vai esi šī persona: %1").arg(vu[a]));
    QAbstractButton* pButtonAtnacu = msgBox.addButton(tr("Jā, atnācu"), QMessageBox::YesRole);
    QAbstractButton* pButtonsaizgaju = msgBox.addButton(tr("Jā, aizeju"), QMessageBox::YesRole);
    msgBox.addButton(tr("Nē"), QMessageBox::NoRole);
    msgBox.exec();

    if (msgBox.clickedButton()==pButtonAtnacu) {
        int darbiba=0;
        db.jauns_apmeklejums(predicted_label, darbiba); //darbība tiek pievieota datu bāzē
    }
    if (msgBox.clickedButton()==pButtonsaizgaju) {
        int darbiba=1;
         db.jauns_apmeklejums(predicted_label, darbiba);//darbība tiek pievieota datu bāzē
    }

}

void MainWindow::on_pushButton_8_clicked()
{
    skatit_pers skat;
    skat.setModal(true);
    skat.exec();
}

void MainWindow::on_pushButton_10_clicked()
{
    rediget red;
    red.setModal(true);
    red.exec();
}

//funkcija, kas parāda redzamus dažādus objektus, šis ir vajadzīgs administratora skatam
void MainWindow::paradit1(){
    ui->pievienot_cilveku->setVisible(true);
    ui->pushButton->setVisible(true);
    ui->pushButton_2->setVisible(true);
    ui->pushButton_6->setVisible(true);
    ui->pushButton_8->setVisible(true);
    ui->pushButton_10->setVisible(true);
    ui->progressBar->setVisible(true);
    ui->pievienot_bildes->setVisible(true);
    ui->comboBox->setVisible(true);
    ui->pushButton_11->setVisible(true);
    ui->pushButton_14->setVisible(true);
}

//noslēpj dažādus objektus
void MainWindow::slept(){
    ui->pievienot_cilveku->setVisible(false);
    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    ui->pushButton_6->setVisible(false);
    ui->pushButton_8->setVisible(false);
    ui->pushButton_10->setVisible(false);
    ui->progressBar->setVisible(false);
    ui->pievienot_bildes->setVisible(false);
    ui->comboBox->setVisible(false);
    ui->pushButton_11->setVisible(false);
    ui->pushButton_14->setVisible(false);
}

//funkcija, kas ir atbildīga par personas pieslēgšanos sistēmā
void MainWindow::on_pushButton_5_clicked()
{
    QString username=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();
    QVector<QString> paroles;
    QVector<QString> lietotajvardi;
    QVector<QString> paroles2;
    QVector<QString> lietotajvardi2;

    lietotajvardi=db.pieejas(paroles);
    lietotajvardi2=db.pieejas2(paroles2);
     int a =1;
     for(int h=0;h<lietotajvardi.size(); h++){
         if(lietotajvardi[h]==username && paroles[h]==password) { a=2;}
     }
     for(int g=0;g<lietotajvardi2.size(); g++){
         if(lietotajvardi2[g]==username && paroles2[g]==password) { a=3;}
     }

    if(a==2){
        QString zinojums = "Sveiks, administrator!";
        paradit1();
        ui->lineEdit->setVisible(false);
        ui->lineEdit_2->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_3->setVisible(false);
        ui->pushButton_5->setVisible(false);
        ui->pushButton_7->setVisible(false);
        ui->label_5->setText(zinojums);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
    }
  if(a==3){
      skatit_pers skat;
      skat.setModal(true);
      skat.exec();
      ui->lineEdit->clear();
      ui->lineEdit_2->clear();
    }
  if (a==1) QMessageBox::information(this,tr(" "), tr("Nepareizs lietotājvārds un/vai parole"));

}

//iziešanai no administratora konta
void MainWindow::on_pushButton_14_clicked()
{
    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Vai tiešām?",
                                 QString("Vai vēlies iziet no šī konta"),
        QMessageBox::Ok | QMessageBox::Cancel);

    if (reply == QMessageBox::Ok) {
        slept();
        ui->lineEdit->setVisible(true);
        ui->lineEdit_2->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_3->setVisible(true);
        ui->pushButton_5->setVisible(true);
        ui->pushButton_14->setVisible(false);
        ui->pushButton_7->setVisible(true);
        ui->label_5->clear();
    }

}
//atver dzēst logu
void MainWindow::on_pushButton_11_clicked()
{
    dzest dzestt;
    dzestt.setModal(true);
    dzestt.exec();
}
//pievieno konkrētai personai bildes
void MainWindow::on_pievienot_bildes_clicked()
{

    if (sejas.size()!=10) QMessageBox::information(this,tr(" "), tr("Nav pietiekami daudz bildes, nevar pievienot personai"));
    else{
        int id=ui->comboBox->currentIndex();
        int ID_ist=ID1[id];
        db.pievienot_bildes(ID_ist,sejas);
    }
}

void MainWindow::paradit(){
    QVector <QString> vardi;
    vardi=db.vardsuzvards_navbildes(ID1);
    ui->comboBox->clear();
    for (int i=0; i<vardi.size(); i++){
        ui->comboBox->addItem(vardi[i]);
    }
}
