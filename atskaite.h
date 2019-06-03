#ifndef ATSKAITE_H
#define ATSKAITE_H

#include <QDialog>


namespace Ui {
class atskaite;
}

class atskaite : public QDialog
{
    Q_OBJECT

public:
    explicit atskaite(QWidget *parent = nullptr);
    ~atskaite();

private:
    Ui::atskaite *ui;
    void paradit();
};

#endif // ATSKAITE_H
