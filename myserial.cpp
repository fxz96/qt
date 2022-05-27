#include "myserial.h"

MySerial::MySerial()
{
    serial_picture();
    sacnSerialPort();
    connectSerial();
}

MySerial::~MySerial()
{

}
void MySerial::serial_picture()
{
     serialWidget = new QWidget;
     serialLayout = new QVBoxLayout;
     serialcom = new QComboBox(serialWidget);
     serialWidget->setLayout(serialLayout);

     openSerial = new QPushButton(serialWidget);
     flushBtn = new QPushButton(serialWidget);
     flushBtn->setText("刷新");
     openSerial->setText("打开串口");

     serialLayout->addWidget(serialcom);
     serialLayout->addWidget(openSerial);
     serialLayout->addWidget(flushBtn);

     myserialport = new QSerialPort(this);

     scanSerialTimer = new QTimer(this);
     scanSerialTimer->start(1000);
}

void MySerial::connectSerial()
{
    connect(scanSerialTimer,SIGNAL(timeout()),this,SLOT(sacnSerialPort()));
    connect(openSerial,SIGNAL(clicked()),this,SLOT(openserial()));
    connect(flushBtn,SIGNAL(clicked()),this,SIGNAL(serialOpenSignal()));

    connect(myserialport,SIGNAL(readyRead()),this,SLOT(receive()));

    connect(myserialport,&QSerialPort::errorOccurred, this, [=](QSerialPort::SerialPortError error){
        if(error == QSerialPort::PermissionError)
        {
            openSerial->setText("打开串口");
            myserialport->close();
            serialcom->setEnabled(true);
            QMessageBox::about(NULL,"错误","串口异常");
        }
    });
}

void MySerial::sacnSerialPort()
{
    serialcom->clear();
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        serialcom->addItem(info.portName());
    }
}

void MySerial::openserial()
{
    if(openSerial->text() == "打开串口")
    {
        myserialport->setPortName(serialcom->currentText());
        myserialport->setBaudRate(115200);
        myserialport->setDataBits(QSerialPort::Data8);
        myserialport->setParity(QSerialPort::NoParity);
        myserialport->setStopBits(QSerialPort::OneStop);
        myserialport->setFlowControl(QSerialPort::NoFlowControl);
        if(myserialport->open(QIODevice::ReadWrite))
        {
            serialcom->setEnabled(false);
            openSerial->setText("关闭串口");
            emit serialOpenSignal();
            //BLMessWidget->setEnabled(true);
        }else
        {
            QMessageBox::about(NULL,"错误","串口被占用，无法打开");
        }
    }else
    {
        myserialport->close();
        serialcom->setEnabled(true);
        openSerial->setText("打开串口");
    }
}

void MySerial::send(QString at)
{
    if(openSerial->text() == "关闭串口")
    {
        myserialport->write(at.toUtf8());
    }
    else
    {
        //QMessageBox::about(NULL,"错误","请打开串口");
    }
}

void MySerial::receive()
{
    QByteArray buf = myserialport->readAll();
    static QString data;

    emit rece_text(buf);
    data.append(buf);
    qint8 start,end;
    {
        while(1)
        {
            start = data.indexOf('\r');

            end = data.indexOf('\n',start+2);

            if(end <= 0)
            {
                break;
                continue;
            }
            if(end -start < 4)
            {
                data = data.mid(start+1);
                continue;
            }
            receiveData << data.mid(start+2,end-3);//qDebug()<<data.mid(start+2,end-3);
            data = data.mid(end+1);

        }
    }
    emit process_data();
}
