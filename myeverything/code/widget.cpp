#include "widget.h"
#include "ui_widget.h"
#include"cnlhelper.h"
#include <QDir>
#include <QtDebug>
#include <QFileDialog>
#include <QSettings>
#include <QProcess>
#include <QMessageBox>
#include <QDesktopServices>
#include<QDateTime>
#include<QFileIconProvider>
#include<QDesktopServices>
#include<windows.h>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("文件搜索");
    //ui->tableWidget->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
   QSettings *configIni = new QSettings("./config.ini", QSettings::IniFormat);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setShowGrid(false);//隐藏表格边框
    ui->tableWidget->verticalHeader()->setVisible(false);//隐藏表格行号
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->lineEdit->setText("C:/Users/Public/Desktop");
    opendir();
    //ui->label_retrieval->setText(configIni->value("path").toString());
    //设置右键菜单
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    popMenu=new QMenu(ui->tableWidget);
    action1=new QAction("打开",this);
    action2=new QAction("删除",this);
    connect(action1,SIGNAL(triggered(bool)),this,SLOT(openfile()));
    connect(action2,SIGNAL(triggered(bool)),this,SLOT(deleterow()));
    //文件夹监视器
    mywatcher.addPath(ui->lineEdit->text());
    connect(&mywatcher,SIGNAL(directoryChanged(QString)),this,SLOT(opendir()));
    delete configIni;
    atom=GlobalAddAtom("a");
    BOOL a=RegisterHotKey((HWND)winId(),atom,MOD_ALT,VK_SPACE);
    if(a)
        qApp->installNativeEventFilter(this);
}

//文件大小格式转化为字符串
QString Widget::translate(quint64 filesize)
{
    QStringList units;
        units << "B" << "KB" << "MB" << "GB" << "TB" << "PB";
        double mod  = 1024.0;
        double size = filesize;
        //qDebug() << size;
        int i = 0;
        long rest = 0;
        while (size >= mod && i < units.count()-1 )
        {
            rest= (long)size % (long)mod ;
            size /= mod;
            i++;
        }
        QString szResult = QString::number(floor(size));
        if( rest > 0)
        {
           szResult += QString(".") + QString::number(rest).left(2);
        }
        szResult += units[i];
        return  szResult;
}




Widget::~Widget()
{
    delete ui;
   BOOL b=UnregisterHotKey((HWND)winId(),atom);
   GlobalDeleteAtom(atom);
}

//windows系统消息过滤
bool Widget::nativeEventFilter(const QByteArray &eventType, void *msg, long *)
{
    if(eventType=="windows_generic_MSG")
    {
        MSG *pmsg=reinterpret_cast<MSG*>(msg);
        if((WM_HOTKEY==pmsg->message)&&((UINT)LOWORD(pmsg->lParam)==MOD_ALT)&&((UINT)HIWORD(pmsg->lParam)==VK_SPACE)){
            if(this->isHidden())
                this->show();
            else
                this->hide();
            return true;
        }
        return false;
    }
    return false;
}

//将fileinfo信息展示到tablewidget的第count行
void Widget::showitem(QFileInfo fileInfo,int count)
{
    QTableWidgetItem *item1=new QTableWidgetItem;
    QFileIconProvider provider;
    QIcon icon = provider.icon(fileInfo);
    item1->setIcon(icon);
    item1->setText(fileInfo.fileName());
    ui->tableWidget->insertRow(count);
    ui->tableWidget->setItem(count,0,item1);
    ui->tableWidget->setItem(count,1,new QTableWidgetItem(fileInfo.path()));

    if(fileInfo.isFile())
    ui->tableWidget->setItem(count,2,new QTableWidgetItem(translate(fileInfo.size())));
    else
         ui->tableWidget->setItem(count,2,new QTableWidgetItem(QString("")));
}




//更改目录
void Widget::on_pushButton_retrieval_clicked()
{
    ui->lineEdit->setText(QFileDialog::getExistingDirectory());
    QSettings *configIni = new QSettings("./config.ini", QSettings::IniFormat);
    configIni->setValue( "path" ,ui->lineEdit->text());
    delete configIni;
}


//右键菜单槽函数
void Widget::on_tableWidget_customContextMenuRequested(const QPoint &pos)
{
    popMenu->addAction(action1);
    popMenu->addAction(action2);
    popMenu->exec(QCursor::pos());
}
//删除行
void Widget::deleterow()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}
//打开文件
void Widget::openfile()
{
    QTableWidgetItem *item1=ui->tableWidget->item(ui->tableWidget->currentRow(),0);
    QTableWidgetItem *item2=ui->tableWidget->item(ui->tableWidget->currentRow(),1);
    //QTableWidgetItem *item=ui->tableWidget->currentItem();
    QString str=item2->text()+"/"+item1->text();
    QDesktopServices::openUrl(QUrl::fromLocalFile(str));
}
//载入目录下的文件
void Widget::opendir()
{
    QDir dir(ui->lineEdit->text());
    dir.setFilter(QDir::Dirs | QDir::Files|QDir::NoDotAndDotDot);
    dir.setSorting(QDir::DirsFirst);//先目录后文件
    list = dir.entryInfoList();
   ui->tableWidget->clearContents();//清空表格
   ui->tableWidget->setRowCount(0);//设行数为0
   for(int i=0;i<list.size();i++)
   {
        QFileInfo fileInfo = list.at(i);
        QTableWidgetItem *item1=new QTableWidgetItem;
        QFileIconProvider provider;
        QIcon icon = provider.icon(fileInfo);
        item1->setIcon(icon);
        item1->setText(fileInfo.fileName());
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i,0,item1);
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(fileInfo.path()));

        if(fileInfo.isFile())
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(translate(fileInfo.size())));
        else
             ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString("")));
   }
}


//监控输入框，文本改变后重新正则匹配排序载入
void Widget::on_lineEdit_retrieval_textChanged(const QString &arg1)
{
    if(ui->lineEdit_retrieval->text()!=""){
        QString str1="^"+ui->lineEdit_retrieval->text()+"$";
        QString str2="^"+QString(ui->lineEdit_retrieval->text().at(0));
        QString str3=ui->lineEdit_retrieval->text();
        QRegularExpression re1(str1,QRegularExpression::CaseInsensitiveOption);
        QRegularExpression re2(str2,QRegularExpression::CaseInsensitiveOption);
        QRegularExpression re3(str3,QRegularExpression::CaseInsensitiveOption);
        QFileInfoList list1;
        QFileInfoList list2;
        QFileInfoList list3;
        QFileInfoList list4;
        ui->tableWidget->clearContents();//清空表格
        ui->tableWidget->setRowCount(0);//设行数为0
        for(int i=0;i<list.size();i++){
            QFileInfo fileInfo = list.at(i);
            QRegularExpressionMatch match1=re1.match(CNLHelper::Instance()->CNToEL(fileInfo.completeBaseName()));//中文转化为拼音首字母，字母数组则不变
            QRegularExpressionMatch match2=re3.match(CNLHelper::Instance()->CNToEL(fileInfo.completeBaseName()));
            QRegularExpressionMatch match3=re2.match(CNLHelper::Instance()->CNToEL(fileInfo.completeBaseName()));
            if(match1.hasMatch()){
                list1.append(fileInfo);
            }
            else if(match2.hasMatch()){
                list2.append(fileInfo);
            }
            else if(match3.hasMatch())
                list3.append(fileInfo);
            else
                list4.append(fileInfo);
        }
        int count=0;
        for(int i=0;i<list1.size();i++)
        {
             QFileInfo fileInfo = list1.at(i);
             showitem(fileInfo,count);
             count++;
        }
        for(int i=0;i<list2.size();i++)
        {
             QFileInfo fileInfo = list2.at(i);
             showitem(fileInfo,count);
             count++;
        }
        for(int i=0;i<list3.size();i++)
        {
             QFileInfo fileInfo = list3.at(i);
             showitem(fileInfo,count);
             count++;
        }
        for(int i=0;i<list4.size();i++){
            QFileInfo fileInfo = list4.at(i);
            showitem(fileInfo,count);
            count++;
        }
    }
}

//监控母录选择框，文本改变后不排序重新载入
void Widget::on_lineEdit_textChanged(const QString &arg1)
{
    opendir();
}
