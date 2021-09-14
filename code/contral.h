#ifndef CONTRAL_H
#define CONTRAL_H

#include <QWidget>

namespace Ui {
class contral;
}

class contral : public QWidget
{
    Q_OBJECT

public:
    explicit contral(QWidget *parent = 0);
    ~contral();
signals:
    void contral_back();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::contral *ui;
    bool mainlight=false;
    bool littlelight=false;
    bool tv=false;
    bool aircondition=false;
    int temperature=20;

};

#endif // CONTRAL_H
