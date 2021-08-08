#include "widget.h"
#include<windows.h>
#include <QApplication>
#include<QAbstractNativeEventFilter>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.hide();
    return a.exec();
}
