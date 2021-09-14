#ifndef MUSIC_H
#define MUSIC_H

#include <QWidget>
#include<QMediaPlayer>
#include<QListWidgetItem>

namespace Ui {
class music;
}

class music : public QWidget
{
    Q_OBJECT

public:
    explicit music(QWidget *parent = 0);
    void showlist();
    void startmusic();
    ~music();
signals:
    void mcsignal();

private slots:
    void on_pushButton_6_clicked();



    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::music *ui;
     QMediaPlayer *play=new QMediaPlayer(this);
     int flag=1;
     int volume=25;
};

#endif // MUSIC_H
