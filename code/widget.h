#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"mainwidget.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void returnlogin();

private:
    Ui::Widget *ui;
    mainwidget mw;
    int pid=10086;
    int pwd=10086;
};

#endif // WIDGET_H
