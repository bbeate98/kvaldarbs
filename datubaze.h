#ifndef DATUBAZE_H
#define DATUBAZE_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"
#include "QString"
#include "QVector"
#include "string"
#include <QDate>



class datubaze
{
public:

    datubaze();
    bool piesl=false;
    void aizvert_datubazi();
    void pievienot_cilveku(QString vards, QString uzvards);
    void paradit_visus();
    void dzest(int id);
    void pievienot_adresi(QString iela, QString nummurs, QString pilseta, QString pasts);
    void pievienot_piekluvi(QString lietotajvards, QString parole, int ID, int atlauja);
    void pievienot_ligumu(QString nummurs, QDate sakums, int slodze, QDate beigas);
    void pievienot_amatu(QString nosaukums, QString apraksts);
    void pievienot_kontaktinfo(QString tel, QDate datums, int id_pers, int id_adrese, int id_amats, int id_ligums);
    void dzest_bildes(int id);
    void dzest_adresi(int id);
    void dzest_ligumu(int id);
    void dzest_amatu(int id);
    void dzest_piekluvi(int id);
    void apmeklejums(int id);
    void dzest_personas_bildes(int id);
    void jauns_apmeklejums(int id, int darbiba);
    void iegut_vard_uzvardu(int id, QString &vards, QString &uzvards);
    void rediget_vardu(int id, QString vards);
    void rediget_uzvardu(int id, QString uzvards);
    void rediget_telefons(int id, QString telefons);
    void rediget_dzimsanas_datumu(int id, QDate dzimsanas_datums);
    void rediget_amatu(int id, int amats);
    void rediget_ligumu(int id, int ligums);
    void rediget_adresi(int id, int adrese);
    void pievienot_bildes(int a, std::vector<cv::Mat> bildes);
    void iegut_apmeklejumus(int a, QVector<QDate> &datumi, QVector<int> &darbibas, QVector<QTime> &laiki, QDate sakums, QDate beigas);
    std::vector<int> iegut_nummurus();
    std::vector<cv::Mat> apskatit_pers_bildes(int d);
    std::vector<cv::Mat> iegut_bildes(std::vector<int> &nummuri);
    QVector<QString> pieejas (QVector<QString> &parole);
    QVector<QString> pieejas2 (QVector<QString> &parole);
    QVector<QString> vardsuzvards_kinfo( QVector <int> &index);
    QVector<QString> vardsuzvards_irpies( QVector <int> &index);
    QVector<QString> vardsuzvards_irbildes( QVector <int> &index);
    QVector<QString> vardsuzvards_navbildes( QVector <int> &index);
    QVector<QString> neizmantotas_adreses( QVector <int> &index);
    QVector<QString> neizmantotie_ligumi( QVector <int> &index);
    QVector<QString> neizmantotie_amati( QVector <int> &index);
    QVector<QString> piekluves(QVector <int> &index);
    QVector<QString> vardsuzvards1( QVector <int> &index);
    QVector<QString> amati(QVector <int> &index);
    QVector<QString> vardsuzvards();
    QVector<QString> lietotajvards();
    QVector<QString> ligumi(QVector <int> &index);
    QVector<QString> adrese(QVector <int> &index);
    void visi_dati (int ID, QString &vards, QString &uzvards, QString &tel_nr, QString &amats, QString &ligums, QDate &dz_dat,QString &adrese);


    ~datubaze();
};

#endif // DATUBAZE_H
