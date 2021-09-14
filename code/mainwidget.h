#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include"music.h"
#include"weather.h"
#include"contral.h"

namespace Ui {
class mainwidget;
}

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainwidget(QWidget *parent = 0);
    ~mainwidget();

private slots:

    void on_closebutton_clicked();
    void on_pushButton_3_clicked();
    void mcreturn();
    void weather_return();
    void contral_return();

    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

signals:
    void mysignal();

private:
    Ui::mainwidget *ui;
    music mc;
    weather wt;
    contral mycontral;
};

#endif // MAINWIDGET_H
