#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QTextTable>
#include <QTextCursor>
#include <QButtonGroup>
#include <QRadioButton>
#include <QList>
#include <QTimer>
#include <regex>

#include <myserial.h>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

/***程序全局变量***/
private:
    /***记录蓝牙模式***/
    qint8 model[4] = {0,1,2,3};
    QString at_query[12];
    qint8 at_query_cnt = 0;

    QList <QString> BlMac;

    qint8 macNumber;

    QList <QString> atLink;

    qint8 fistFlag = 0;

    //QString atinit[4] = {"AT+RESTORE\r\n","AT+SSP=0\r\n","AT+PIN=13579\r\n",""};


/***函数****/
private:

    /***变量初始化****/
    void varite_init();
    /**画面初始化**/
    void pictureLayout_init();
    void picture_init();

    /***槽、信号连接****/
    void connect_init();


/***UI界面****/
private:

    /**画面布局**/
    /**主布局，网格布局**/
    QWidget * mainWidget;
    QGridLayout *mainLayout;

    /***蓝牙信息栏***/
    QHBoxLayout *BlMessHBoxLayout[2];
    QFormLayout *BlMessFormLayout[8];

    /***本机蓝牙***/
    QWidget * LocalBlWidget;
    QHBoxLayout * LocalBlHBox;

    /***蓝牙设置窗口***/
    QWidget * BlSetWidget;
    QHBoxLayout *BlSetItemHBox[4];
    QWidget * BlSetItemWidget[4];

    /***自定义发送区***/
    QWidget *customWidget;
    QVBoxLayout *customLayout;
    QPushButton *cleanOut,*cleanIn,*sendBtn;

/***画面控件***/
private:
    /***蓝牙信息显示框****/
    QLineEdit *BlMessLine[8];

    /***蓝牙发送控件***/
    QLabel *BlSetLabel[4];
    QButtonGroup *BlMessGroup[4];
    QButtonGroup *BlSetGroup;
    QRadioButton *BlMessRadio[4][4];
    QLineEdit *BlSetLine[4];
    QPushButton *BlSetBtn[4];

    /***本机蓝牙***/
    QFormLayout *LocalBlForm[2];
    QLineEdit *LocalBlLine[2];
    QPushButton *LocalMessClear,*LookBt;

    /***蓝牙发送、回复文本***/
    QTextEdit *BlReciveText,*BlSendText;

    /***串口***/
    MySerial *sport;
    QThread *serialThread;

    /***定时器***/
    QTimer *at_query_timer;
    QTimer *at_link_timer;
    QTimer *at_bl_init;

signals:
    void macFlush();

private slots:

    /***状态选择***/
    void radiochange(int id, bool checked);

    /***蓝牙建立连接，配对***/
    void BlLink(int id);

    /***清空配置参数***/
    void BlSetMacClear();

    /***接收数据处理****/
    void process();

    /***接收数据***/
    void receive_text(QString str);

    /***启动查询定时器***/
    void startQuery();

    /***联机查询***/
    void startupQuery();

    /***配对提示***/
    void pair();

    /***建立连接***/
    void setLink();

    /***查看配对***/
    void lookLink();

    /****清空发送区****/
    void cleanTextOut();

    /****清空接收区***/
    void cleanTextIn();

    /****发送自定义指令*****/
    void sendText();

    void test(QAbstractButton *button, bool checked);

};
#endif // MAINWINDOW_H
