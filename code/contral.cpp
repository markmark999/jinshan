#include "contral.h"
#include "ui_contral.h"

contral::contral(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::contral)
{
    ui->setupUi(this);
    ui->label_7->setText(QString::number(temperature));
    setFixedSize(this->width(), this->height());
}

contral::~contral()
{
    delete ui;
}

void contral::on_pushButton_2_clicked()
{
    if(!mainlight){
        ui->textBrowser->append(QString("客厅灯打开！"));
        mainlight=true;
    }
    else{
        ui->textBrowser->append(QString("客厅灯关闭！"));
        mainlight=false;
    }
}

void contral::on_pushButton_clicked()
{
    emit contral_back();
}

void contral::on_pushButton_3_clicked()
{
    if(!littlelight){
        ui->textBrowser->append(QString("卧室灯打开！"));
        littlelight=true;
    }
    else{
        ui->textBrowser->append(QString("卧室灯关闭！"));
        littlelight=false;
    }
}

void contral::on_pushButton_4_clicked()
{
    if(!tv){
        ui->textBrowser->append(QString("电视打开！"));
        tv=true;
    }
    else{
        ui->textBrowser->append(QString("电视关闭！"));
        tv=false;
    }
}

void contral::on_pushButton_5_clicked()
{
    if(!aircondition){
        ui->textBrowser->append(QString("空调打开！"));
        aircondition=true;
    }
    else{
        ui->textBrowser->append(QString("空调关闭！"));
        aircondition=false;
    }
}

void contral::on_pushButton_6_clicked()
{
    if(!aircondition){
        ui->textBrowser->append(QString("空调没打开！"));

    }
    else{
        temperature++;
        ui->label_7->setText(QString::number(temperature));
        ui->textBrowser->append(QString("空调温度调高一度！"));
    }
}

void contral::on_pushButton_7_clicked()
{
    if(!aircondition){
        ui->textBrowser->append(QString("空调没打开！"));

    }
    else{
        temperature--;
        ui->label_7->setText(QString::number(temperature));
        ui->textBrowser->append(QString("空调温度调低一度！"));
    }
}

void contral::on_pushButton_8_clicked()
{
    ui->textBrowser->clear();
}
