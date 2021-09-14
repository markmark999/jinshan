#ifndef WEATHER_H
#define WEATHER_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QTextCodec>
namespace Ui {
class weather;
}

class weather : public QWidget
{
    Q_OBJECT

public:
    explicit weather(QWidget *parent = 0);
    void data_utf8_encode(QString &data);
    void send_request_message(QString ct);
    ~weather();
signals:
    void weather_back();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void deal_reply_msg();

private:
    Ui::weather *ui;
    QNetworkAccessManager *manager; //定义网络操作对象类
    QNetworkReply *reply;

    QString city;  //城市
    QString wind; //风向
};

#endif // WEATHER_H
