#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    varite_init();
    pictureLayout_init();
    picture_init();
    connect_init();
}

MainWindow::~MainWindow()
{
}

/***变量初始化***/
void MainWindow::varite_init()
{
    /**命令初始化**/
    at_query[0] = "+ADDR";
    at_query[1] = "+PIN";
    at_query[2] = "+NAME";
    at_query[3] = "+SPKVOL";
    at_query[4] = "+MICGAIN";
    at_query[5] = "+SSP";
    at_query[6] = "+PROFILE";
    at_query[7] = "+VER";

    at_query[8] = "+RESTORE";
    at_query[9] = "+PIN=13579";
    at_query[10] = "+SSP=0";
}

/***画面布局****/
void MainWindow::pictureLayout_init()
{
    this->resize(800,480);
    /**网格布局**/
    mainWidget = new QWidget(this);
    mainWidget->setGeometry(0,0,800,480);
    mainLayout = new QGridLayout(mainWidget);
    mainWidget->setLayout(mainLayout);

    /**网格表格设置**/
    mainLayout->setColumnStretch(0,5);
    mainLayout->setColumnStretch(1,5);
    mainLayout->setColumnStretch(2,5);
    mainLayout->setColumnStretch(3,5);
    mainLayout->setColumnStretch(4,4);

    mainLayout->setRowStretch(0,2);
    mainLayout->setRowStretch(1,2);
    mainLayout->setRowStretch(2,2);
    mainLayout->setRowStretch(3,10);
    mainLayout->setRowStretch(4,10);

    /**蓝牙信息栏布局**/
    BlMessHBoxLayout[0] = new QHBoxLayout;
    BlMessHBoxLayout[1] = new QHBoxLayout;
    for (qint8 i = 0; i < 8; i++ ) {
        BlMessFormLayout[i] = new QFormLayout;
    }
    mainLayout->addLayout(BlMessHBoxLayout[0],0,0,1,4);
    mainLayout->addLayout(BlMessHBoxLayout[1],1,0,1,4);
    for (qint8 i = 0; i < 4; i++ ) {
        BlMessHBoxLayout[0]->addLayout(BlMessFormLayout[i]);
    }
    for (qint8 i = 4; i < 8; i++ ) {
        BlMessHBoxLayout[1]->addLayout(BlMessFormLayout[i]);
    }


    /***本机蓝牙***/
     LocalBlWidget = new QWidget(this);
     LocalBlHBox = new QHBoxLayout(LocalBlWidget);
     LocalBlWidget->setLayout(LocalBlHBox);
     mainLayout->addWidget(LocalBlWidget,2,0,1,4);

     LocalBlForm[0] = new QFormLayout;
     LocalBlForm[1] = new QFormLayout;


    /***蓝牙设置区***/
    BlSetWidget = new QWidget(this);
    //BlSetWidget->resize(300,200);
    //BlSetWidget->setStyleSheet("QWidget{ background-color: rgba(255, 245,238, 100%); }");

    mainLayout->addWidget(BlSetWidget,3,0,1,4);

    for (qint8 i = 0; i < 4 ; i++ ) {
         BlSetItemHBox[i] = new QHBoxLayout;
         BlSetItemWidget[i] = new QWidget(BlSetWidget);
         BlSetItemWidget[i]->setLayout(BlSetItemHBox[i]);
    }
    BlSetItemWidget[0]->setGeometry(0,0,550,40);
    BlSetItemWidget[1]->setGeometry(0,40,550,40);
    BlSetItemWidget[2]->setGeometry(0,80,550,40);
    BlSetItemWidget[3]->setGeometry(0,120,550,40);

    /***自定义发送区***/
    customWidget = new QWidget;
    customLayout = new QVBoxLayout;
    mainLayout->addWidget(customWidget,4,4,1,1);
    customWidget->setLayout(customLayout);
}

/***画面控件***/
void MainWindow::picture_init()
{
    /***蓝牙信息窗口***/
    for (qint8 i = 0; i < 8; i++ ) {
        BlMessLine[i] = new QLineEdit(this);
        BlMessLine[i]->setReadOnly(true);
    }
    BlMessFormLayout[0]->addRow("固件版本：",BlMessLine[0]);
    BlMessFormLayout[1]->addRow("名称：",BlMessLine[1]);
    BlMessFormLayout[2]->addRow("密码：",BlMessLine[2]);
    BlMessFormLayout[3]->addRow("设备地址",BlMessLine[3]);
    BlMessFormLayout[4]->addRow("喇叭音量：",BlMessLine[4]);
    BlMessFormLayout[5]->addRow("麦克增益：",BlMessLine[5]);
    BlMessFormLayout[6]->addRow("配对方式：",BlMessLine[6]);
    BlMessFormLayout[7]->addRow("PROFILE：",BlMessLine[7]);

     /***本机蓝牙***/

      LocalBlLine[0] = new QLineEdit(LocalBlWidget);
      LocalBlLine[1] = new QLineEdit(LocalBlWidget);

      LocalBlForm[0]->addRow("本地模式",LocalBlLine[0]);
      LocalBlForm[1]->addRow("本地地址",LocalBlLine[1]);

      LocalMessClear = new QPushButton(LocalBlWidget);
      LocalMessClear->setText("清空地址");
      LookBt = new QPushButton(LocalBlWidget);
      LookBt->setText("查看");

      LocalBlLine[0]->setReadOnly(true);
      LocalBlLine[1]->setReadOnly(true);

      LocalBlHBox->addLayout(LocalBlForm[0]);
      LocalBlHBox->addLayout(LocalBlForm[1]);
      LocalBlHBox->addWidget(LocalMessClear);
      LocalBlHBox->addWidget(LookBt);

    /***蓝牙设置区***/

    for(qint8 i = 0; i < 4; i++)
    {
        BlMessGroup[i] = new QButtonGroup(BlSetItemWidget[i]);
        for (qint8 j = 0; j < 4 ; j++ ) {
            BlMessRadio[i][j] = new QRadioButton(BlSetItemWidget[i]);
            BlMessGroup[i]->addButton(BlMessRadio[i][j],j+i*4);
        }
        BlMessRadio[i][0]->setText("大板SINK");
        BlMessRadio[i][1]->setText("大板SOURCE");
        BlMessRadio[i][2]->setText("小板SINK");
        BlMessRadio[i][3]->setText("小板SOURCE");

        BlMessRadio[i][i]->setChecked(true);

        BlSetLine[i] = new QLineEdit(BlSetWidget);
        BlSetBtn[i] = new QPushButton(BlSetWidget);
        BlSetBtn[i]->setText("建立连接");

        BlSetItemHBox[i]->addWidget(BlMessRadio[i][0]);
        BlSetItemHBox[i]->addWidget(BlMessRadio[i][1]);
        BlSetItemHBox[i]->addWidget(BlMessRadio[i][2]);
        BlSetItemHBox[i]->addWidget(BlMessRadio[i][3]);

        BlSetItemHBox[i]->addWidget(BlSetLine[i]);
        BlSetItemHBox[i]->addWidget(BlSetBtn[i]);
    }


    BlSetGroup = new QButtonGroup;
    for(qint8 i = 0; i < 4; i++)
    {
        BlSetGroup->addButton(BlSetBtn[i],i);
    }


    /***蓝牙指令发送回复区***/
    BlReciveText = new QTextEdit(this);
    BlSendText = new QTextEdit(this);
    mainLayout->addWidget(BlReciveText,4,0,1,2);
    mainLayout->addWidget(BlSendText,4,2,1,2);

    /***串口***/
    sport = new MySerial;
    //sport->moveToThread(serialThread);
    mainLayout->addWidget(sport->serialWidget,0,4,2,1);

    /***自定义发送区***/
    cleanOut = new QPushButton(customWidget);
    cleanIn = new QPushButton(customWidget);
    sendBtn = new QPushButton(customWidget);

    cleanIn->setText("清除接收区");
    cleanOut->setText("清除发送区");
    sendBtn->setText("发送");
    customLayout->addWidget(cleanIn);
    customLayout->addWidget(cleanOut);
    customLayout->addWidget(sendBtn);

    /***定时器***/
    at_query_timer = new QTimer(this);
    at_link_timer = new QTimer(this);
    at_bl_init = new QTimer(this);
}


/****连接函数****/
void MainWindow::connect_init()
{
    /***模式选择***/
    connect(BlMessGroup[0],SIGNAL(idToggled(int, bool)),this,SLOT(radiochange(int, bool)));
    connect(BlMessGroup[1],SIGNAL(idToggled(int, bool)),this,SLOT(radiochange(int, bool)));
    connect(BlMessGroup[2],SIGNAL(idToggled(int, bool)),this,SLOT(radiochange(int, bool)));
    connect(BlMessGroup[3],SIGNAL(idToggled(int, bool)),this,SLOT(radiochange(int, bool)));
    /******配对提示******/
    connect(this,SIGNAL(macFlush()),this,SLOT(pair()));

    /****蓝牙配对连接****/
    connect(BlSetGroup,SIGNAL(idClicked(int)),this,SLOT(BlLink(int)));

    /***清空配置参数***/
    connect(LocalMessClear,SIGNAL(clicked()),this,SLOT(BlSetMacClear()));

    /***清除发送区***/
    connect(cleanOut,SIGNAL(clicked()),this,SLOT(cleanTextOut()));
    /***清除接收区***/
    connect(cleanIn,SIGNAL(clicked()),this,SLOT(cleanTextIn()));
    /***发送自定义命令***/
    connect(sendBtn,SIGNAL(clicked()),this,SLOT(sendText()));
    /***查看连接***/
    connect(LookBt,SIGNAL(clicked()),this,SLOT(lookLink()));

    /**串口接收输出**/
    connect(sport,SIGNAL(rece_text(QString)),this,SLOT(receive_text(QString)));
    /**串口接收处理**/
    connect(sport,SIGNAL(process_data()),this,SLOT(process()));
    /***串口启动**/
    connect(sport,SIGNAL(serialOpenSignal()),this,SLOT(startQuery()));
    /***串口打开，发送数据***/
    connect(at_query_timer,SIGNAL(timeout()),this,SLOT(startupQuery()));

    connect(at_link_timer,SIGNAL(timeout()),this,SLOT(setLink()));
}

/***模式选择****/
void MainWindow::radiochange(int id, bool checked)
{
    if(!checked)
        return;
    model[id >> 2] = (id & 3);
    if(BlMac.length() > 0)
    {
        emit macFlush();
    }

    if(macNumber == (id >> 2))
    {
        QString at;
        if(model[macNumber] & 0x01)
        {
            at = "AT+PROFILE=67\r\n";
        }else
        {
            at = "AT+PROFILE=160\r\n";
        }

        BlSendText->append(at);
        sport->send(at);
    }
}

void MainWindow::pair()
{
    for (qint8 i = 0; i < 4; i++ )
    {
        BlSetBtn[i]->setEnabled(true);
        if((model[i] ^ model[macNumber]) == 3)
        {
            BlSetBtn[i]->setStyleSheet("QPushButton { background-color: green }");
        }
        else
        {
            BlSetBtn[i]->setStyleSheet("QPushButton { background-color: yellow }");
        }
    }
    BlSetBtn[macNumber]->setEnabled(false);
    BlSetBtn[macNumber]->setStyleSheet("");
    switch (model[macNumber]) {
    case 0:
        LocalBlLine[0]->setText("大板SINK");
        break;
    case 1:
        LocalBlLine[0]->setText("大板SOURCE");
        break;
    case 2:
        LocalBlLine[0]->setText("小板SINK");
        break;
    case 3:
        LocalBlLine[0]->setText("小板SOURCE");
        break;
    }

}

void MainWindow::BlLink(int id)
{
    atLink.clear();

    //atLink<<"AT+RESTORE\r\n";
    //atLink<<"AT+SSP=0\r\n";
    //atLink<<"AT+PIN=13579\r\n";
    if(model[macNumber] & 0x01)
    {
        atLink<<"AT+PROFILE=67\r\n";
    }else
    {
        atLink<<"AT+PROFILE=160\r\n";
    }

    atLink<<"AT+A2DPCONN="+BlSetLine[id]->text()+"\r\n";
    atLink<<"AT+A2DPCONN="+BlSetLine[id]->text()+"\r\n";
    atLink<<"AT+A2DPCONN="+BlSetLine[id]->text()+"\r\n";
    atLink<<"AT+A2DPCONN="+BlSetLine[id]->text()+"\r\n";

    at_link_timer->start(600);
}

/***建立连接***/
void MainWindow::setLink()
{
    static qint8 at_cnt = 0;

    if(at_cnt >= atLink.length())
    {
        at_link_timer->stop();
        at_cnt = 0;
    }else
    {
        BlSendText->append(atLink[at_cnt]);
        sport->send(atLink[at_cnt]);
        at_cnt++;
    }
}

/***启动查询定时器***/
void MainWindow::startQuery()
{
    at_query_cnt = 0;
    if(model[macNumber] & 0x01)
    {
        at_query[11] = "AT+PROFILE=67\r\n";
    }else
    {
        at_query[11] = "AT+PROFILE=160\r\n";
    }
    at_query_timer->start(100);
}

/***查询蓝牙设备信息***/
void MainWindow::startupQuery()
{
    sport->send("AT"+at_query[at_query_cnt]+"\r\n");
    BlSendText->append("AT"+at_query[at_query_cnt]+"\r\n");
    at_query_cnt++;
    if(fistFlag == 0)
    {
        if(at_query_cnt > 7)
        {
            at_query_cnt = 0;
            at_query_timer->stop();
        }
    }
    else
    {
        if(at_query_cnt > 11)
        {
            at_query_cnt = 0;
            at_query_timer->stop();
        }
    }
}

/***输出串口接收信息***/
void MainWindow::receive_text(QString str)
{
    BlReciveText->append(str);
}

/***串口数据处理***/
void MainWindow::process()
{
    QList <QString>& data = sport->receiveData;
    QString item,lin;
    foreach(item,data)
    while(!data.isEmpty())
    {
        item = data[0];
        //qDebug()<<item;
        if(item.contains("OK", Qt::CaseInsensitive))
        {

        }else if(item.contains("ERROR", Qt::CaseInsensitive))
        {

        }
        else
        {
            lin = item.mid(item.indexOf('='));
            lin = lin.mid(1);

            if(item.contains("VER", Qt::CaseInsensitive))
            {
                BlMessLine[0]->setText(lin);
            }
            else if(item.contains("NAME", Qt::CaseInsensitive))
            {
                BlMessLine[1]->setText(lin);
            }
            else if(item.contains("PIN", Qt::CaseInsensitive))
            {
                BlMessLine[2]->setText(lin);
            }
            else if(item.contains("ADDR", Qt::CaseInsensitive))
            {
                BlMessLine[3]->setText(lin);
                LocalBlLine[1]->setText(lin);
                qint8 cnt = 0;
                QString str;
                foreach(str,BlMac)
                {
                    if(str.contains(lin, Qt::CaseInsensitive))
                    {
                        macNumber = cnt;
                        fistFlag = 0;
                        emit macFlush();
                        break;
                        continue;
                    }
                    cnt++;
                }
                if(cnt >= BlMac.length())
                {
                    BlMac << lin;
                    BlSetLine[cnt]->setText(lin);
                    macNumber = cnt;
                    fistFlag = 1;
                    emit macFlush();
                }
            }
            else if(item.contains("SPKVOL", Qt::CaseInsensitive))
            {
                BlMessLine[4]->setText(lin);
            }
            else if(item.contains("MICGAIN", Qt::CaseInsensitive))
            {
                BlMessLine[5]->setText(lin);
            }
            else if(item.contains("SSP", Qt::CaseInsensitive))
            {
                if(lin.contains("0", Qt::CaseInsensitive))
                {
                    BlMessLine[6]->setText("简易配对关闭");
                }else
                {
                    BlMessLine[6]->setText("简易配对开启");
                }
            }
            else if(item.contains("PROFILE", Qt::CaseInsensitive))
            {
                if(lin.contains("160", Qt::CaseInsensitive))
                {
                    BlMessLine[7]->setText("SINK");
                }else if(lin.contains("67", Qt::CaseInsensitive))
                {
                    BlMessLine[7]->setText("SOURCE");
                }else
                {
                    BlMessLine[7]->setText("未知，功能码："+lin);
                }
            }
//            else if(item.contains("PLIST", Qt::CaseInsensitive))
//            {
//                lookstr += lin;
//                lookline->setText(lookstr);
//            }
        }
        data.removeFirst();
    }
}

/***清空配置参数***/
void MainWindow::BlSetMacClear()
{
    QMessageBox tip;
    tip.setText("清除存储的蓝牙地址");
    tip.setInformativeText("确认清除吗？");
    tip.setStandardButtons(QMessageBox::Ok| QMessageBox::Cancel);
    tip.setDefaultButton(QMessageBox::Cancel);
    int key = tip.exec();

    if(key == QMessageBox::Cancel)
    {
        return;
    }
    BlMac.clear();
    for(qint8 i = 0; i < 4; i++)
    {
        BlSetLine[i]->setText("");
        for(qint8 j = 0; j < 4; j++)
        {
            BlMessRadio[i][j]->setChecked(false);
        }
        BlSetBtn[i]->setStyleSheet("");
        BlSetBtn[i]->setEnabled(true);
    }
}

/***查看配对***/
void MainWindow::lookLink()
{
    QString at;
    at = "AT+PLIST\r\n";
    BlSendText->append(at);
    sport->send(at);
    BlReciveText->clear();
}

/****清空发送区****/
void MainWindow::cleanTextOut()
{
    BlSendText->clear();
}

/****清空接收区***/
void MainWindow::cleanTextIn()
{
    BlReciveText->clear();
}

/****发送自定义指令*****/
void MainWindow::sendText()
{
    sport->send(BlSendText->document()->toPlainText()+"\r\n");
}
/***测试函数****/
void MainWindow::test(QAbstractButton * button, bool checked)
{
    if(button == BlMessRadio[0][0])
    {
        qDebug()<<"按钮一:"<<checked;
    }
}
