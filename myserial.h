#ifndef MYSERIAL_H
#define MYSERIAL_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTimer>
#include <QList>
#include <QDebug>

class MySerial: public QObject
{
    Q_OBJECT

public:
    MySerial();
    ~MySerial();

/***串口信息***/
public:

    QList <QString> comlist;

    QList <QString> receiveData;

/***串口窗口***/
public:

    QWidget *serialWidget;
    QVBoxLayout *serialLayout;
    QComboBox *serialcom;
    QPushButton *openSerial,*flushBtn;

    QTimer *scanSerialTimer;

    QSerialPort *myserialport;

/**串口方法**/
private:

    void serial_picture();
    void connectSerial();

signals:

    /**串口打开信号**/
    void serialOpenSignal();

    /***接收数据信号***/
    void rece_text(QString str);

    /***接收数据处理信号***/
    void process_data();

private slots:

    void sacnSerialPort();

    void openserial();

    void receive();

public slots:
    void send(QString at);

};

#endif // MYSERIAL_H
