#include "music.h"
#include "ui_music.h"
#include <QDir>
#include <QMediaPlayer>
#include<QListWidgetItem>
#include<QDebug>
music::music(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::music)
{
    ui->setupUi(this);
    showlist();
    setFixedSize(this->width(), this->height());
    ui->listWidget->setCurrentItem(ui->listWidget->item(0));
    QString str="qrc:/music/"+ui->listWidget->currentItem()->text();
    play->setMedia(QUrl(str));
    play->setVolume(25);
}

void music::showlist()
{
    QString str=":/music/";
    QDir dir(str);
    dir.setFilter(QDir::Dirs | QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);
    QFileInfoList list = dir.entryInfoList();
    for(int i=0;i<list.size();i++)
    {
         QFileInfo fileInfo = list.at(i);
         QListWidgetItem *item=new QListWidgetItem;
         item->setText(fileInfo.fileName());
         ui->listWidget->addItem(item);
    }
}

void music::startmusic()
{
    if(play->PlayingState==3)
    {
        play->stop();
    }
    else{
        QString str="qrc:/music/"+ui->listWidget->currentItem()->text();
        qDebug()<<str;
        play->setMedia(QUrl(str));
        play->setVolume(25);
        play->play();
    }

}

music::~music()
{
    delete ui;
}

void music::on_pushButton_6_clicked()
{
    emit mcsignal();
}


void music::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->pushButton_4->setStyleSheet("border-image: url(:/image/暂停.png);");
    startmusic();
}

void music::on_pushButton_5_clicked()
{
    int row=0;
    if(ui->listWidget->currentRow()==ui->listWidget->model()->rowCount()-1){
//        row=0;
//        ui->listWidget->setCurrentRow(row);
    }
    else{
        row=ui->listWidget->currentRow()+1;
        ui->listWidget->setCurrentRow(row);
    }
    ui->listWidget->setCurrentItem(ui->listWidget->item(row));
    startmusic();
    ui->pushButton_4->setStyleSheet("border-image: url(:/image/暂停.png);");

}

void music::on_pushButton_3_clicked()
{
    int row=0;
    if(ui->listWidget->currentRow()!=0){
       row=ui->listWidget->currentRow()-1;
       ui->listWidget->setCurrentRow(row);
    }
    else{
        row=ui->listWidget->model()->rowCount()-1;
        ui->listWidget->setCurrentRow(row);
    }
    ui->listWidget->setCurrentItem(ui->listWidget->item(row));
    startmusic();
    ui->pushButton_4->setStyleSheet("border-image: url(:/image/暂停.png);");
}


void music::on_pushButton_4_clicked()
{
    if(flag==1){
        ui->pushButton_4->setStyleSheet("border-image: url(:/image/暂停.png);");

        play->play();
        flag=0;
    }
    else{
        ui->pushButton_4->setStyleSheet("border-image: url(:/image/播放.png);");
        play->pause();
        flag=1;
    }
}

void music::on_pushButton_clicked()
{
    if(volume<100){
        volume++;
        play->setVolume(volume);
        ui->label_3->setText(QString::number(volume));
    }
}

void music::on_pushButton_2_clicked()
{
    if(volume>0){
        volume--;
        play->setVolume(volume);
        ui->label_3->setText(QString::number(volume));
    }
}
