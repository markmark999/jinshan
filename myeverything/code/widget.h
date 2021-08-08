#ifndef WIDGET_H
#define WIDGET_H
#include<QMenu>
#include <QWidget>
#include<windows.h>
#include<QAbstractNativeEventFilter>
#include<QDir>
#include<QFileSystemWatcher>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget,public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    QString translate(quint64 filesize);
    Widget(QWidget *parent = nullptr);
    ~Widget();
    virtual bool nativeEventFilter(const QByteArray &eventType, void *msg, long *) Q_DECL_OVERRIDE;
    void showitem(QFileInfo fileInfo,int count);  //将fileinfo对象展示再tablewigget中count行
//    bool FindFile();
private slots:
    void on_pushButton_retrieval_clicked();



    void on_tableWidget_customContextMenuRequested(const QPoint &pos);
    void deleterow();  //删除行
    void openfile();
    void opendir();

    void on_lineEdit_retrieval_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::Widget *ui;
    QFileInfoList list;
    QMenu *popMenu;   //菜单变量
    QAction *action1;        //菜单选项
    QAction *action2;
    ATOM atom;
    QFileSystemWatcher mywatcher;

};
#endif // WIDGET_H
