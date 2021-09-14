#include "mainwidget.h"
#include "ui_mainwidget.h"
#include"music.h"
#include"weather.h"
#include"contral.h"
mainwidget::mainwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);
    connect(&mc,SIGNAL(mcsignal()),this,SLOT(mcreturn()));
    connect(&wt,SIGNAL(weather_back()),this,SLOT(weather_return()));
    connect(&mycontral,SIGNAL(contral_back()),this,SLOT(contral_return()));
    setFixedSize(this->width(), this->height());
}

mainwidget::~mainwidget()
{
    delete ui;
}


void mainwidget::on_closebutton_clicked()
{
    emit mysignal();
}

void mainwidget::on_pushButton_3_clicked()
{
    this->hide();
    mc.show();
}

void mainwidget::mcreturn()
{
    mc.hide();
    this->show();
}

void mainwidget::weather_return()
{
    wt.hide();
    this->show();
}

void mainwidget::contral_return()
{
    mycontral.hide();
    this->show();
}

void mainwidget::on_pushButton_2_clicked()
{
    this->hide();
    wt.show();
}

void mainwidget::on_pushButton_clicked()
{
    this->hide();
    mycontral.show();
}
