#include "widget.h"
#include "ui_widget.h"
#include<QDialog>
#include<QLabel>
#include"mainwidget.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    this->setWindowTitle("智能家居");
    connect(&mw,SIGNAL(mysignal()),this,SLOT(returnlogin()));
    ui->lineEdit->setText("10086");
    ui->lineEdit_2->setText("10086");
    setFixedSize(this->width(), this->height());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    if(ui->lineEdit->text().toInt()==pid){
        if(ui->lineEdit_2->text().toInt()==pwd){
            this->hide();
            mw.show();
        }
        else{
            QDialog* dialog2=new QDialog(this);
            dialog2->setModal(true);
            QLabel* lable2=new QLabel(dialog2);
            lable2->setText("密码错误");
            dialog2->show();
        }
    }
    else{
        QDialog* dialog1=new QDialog(this);
        dialog1->setModal(true);
        QLabel* lable1=new QLabel(dialog1);
        lable1->setText("账号错误");
        dialog1->show();
    }
}

void Widget::returnlogin()
{
    this->show();
    mw.hide();
}
