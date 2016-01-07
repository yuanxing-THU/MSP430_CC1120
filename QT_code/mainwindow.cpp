#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QIODevice>
#include <QTime>
#include <QString>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    serial = new QSerialPort(this);
    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    UART_status = false;
    WORK_status = false;
    QStringList comlist;
    QStringList PAlist;
    comlist<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"<<"COM7"<<"COM8";
    PAlist<<"None"<<"3dbi"<<"5dbi";
    ui->UART_com_num->addItems(comlist);
    ui->PAstatus->addItems(PAlist);
    connect(ui->UART_connect_button,SIGNAL(clicked()),this,SLOT(UART_ACTION()));
    //connect(serial, SIGNAL(readyRead()), this, SLOT(serial_readData()));//UART recieve data
    connect(ui->BEGIN,SIGNAL(clicked()),this,SLOT(BEGIN_ACTION()));
    connect(this,SIGNAL(test_signals()),this,SLOT(test_once()));
    connect(&m_time,SIGNAL(timeout()),SLOT(TimeoutAction()));

    interval = 500;
    correct_rate = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::UART_ACTION(void) //after clicked UART_connect_button
{
    if(UART_status == false )//open uart
    {
        QString currunt_com=ui->UART_com_num->currentText();
        serial->setPortName(currunt_com);
        if(serial->open(QIODevice::ReadWrite)){
            ui->UART_connect_button->setText("DISCONNECT");
            UART_status = true;
            ui->serial_status->setText(tr("Connected!"));
        }else
        {
            QMessageBox::critical(this,tr("Error"),serial->errorString());
        }
    }
    else//close UART
    {
        serial->close();
        ui->UART_connect_button->setText("CONNECT");
        UART_status = false;
        ui->serial_status->setText(tr("Disconnected!"));
    }
}
void MainWindow::BEGIN_ACTION(void)
{
    if(WORK_status == false)
    {
        ui->BEGIN->setText("STOP");
        WORK_status = true;

        test_times = ui->test_times->value();
        currunt_times = test_times;
        message_length = ui->message_len->value();
        Distance = ui->Distance->value();
        PAstatus = ui->PAstatus->currentText();


        char cmessage_length[10];
        char ctest_times[10];
        char cdistance[10];
        QString smessage_length;
        QString stest_times;
        QString sdistance;
        itoa(test_times,ctest_times,10);
        itoa(message_length,cmessage_length,10);
        itoa(Distance,cdistance,10);
        smessage_length = cmessage_length;
        stest_times = ctest_times;
        sdistance = cdistance;
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间



        RXfilename = time.toString("yyyy-MM-dd_hh-mm-ss"); //设置显示格式
        RXfilename+="RX_ml"+smessage_length+"_tt"+stest_times+"_dt"+sdistance+"_PA"+PAstatus+".txt";
        RXfile.setFileName(RXfilename);

        TXfilename = time.toString("yyyy-MM-dd_hh-mm-ss"); //设置显示格式
        TXfilename+="TX_ml"+smessage_length+"_tt"+stest_times+"_dt"+sdistance+"_PA"+PAstatus+".txt";
        TXfile.setFileName(TXfilename);

        if(!RXfile.open(QFile::WriteOnly |QIODevice::Truncate)){
            QMessageBox::warning(this,"RXFile","RXFile cannot open!");
        }else if(!TXfile.open(QFile::WriteOnly |QIODevice::Truncate)){
            QMessageBox::warning(this,"TXFile","TXFile cannot open!");
        }
        else
        {
            emit test_signals();
        }

    }else
    {
        ui->BEGIN->setText("BEGIN");
        WORK_status = false;
        QMessageBox::information(this,"STOP","STOP TEST!");
        RXfile.close();
        TXfile.close();
        ui->realtime_display->setText(0);
    }
}
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
    //QMessageBox::information(this,"info","writedata_over!");
}
void MainWindow::test_once(void)
{
    //QByteArray txdata;
    txdata.clear();
    txdata.append(0xff);
    for(int i = 0;i<message_length ;i++)
    {
        unsigned char c=48+rand()%74;  // ASCII 48~122
        txdata.append(c);
    }
    txdata.append(0xff);
    QTextStream TXout(&TXfile);
    for(int i=0;i<txdata.length();i++)
    {
        TXout<<txdata[i];
    }
    TXout<<"\n";
    if(WORK_status == true)
    {
        writeData(txdata);
        m_time.start(interval);
        char ccurrunt_times[10];
        itoa(currunt_times,ccurrunt_times,10);
        ui->realtime_display->setText(ccurrunt_times);
    }
}
void MainWindow::TimeoutAction(void)
{
    m_time.stop();
    rxdata.clear();
    rxdata = serial->readAll();
    QTextStream RXout(&RXfile);
    for(int i=0;i<rxdata.length();i++)
    {
        RXout<<rxdata[i];
    }
    RXout<<"\n";

    bool tfflag = true;
    for(int i=1;i<=message_length;i++)
    {
        if(txdata[i]!=rxdata[i+1])
        {
            tfflag = false;
            break;
        }
    }
    if(tfflag == true)
    {
        correct_rate++;
    }
    ui->crate->setText(QString::number((int)(correct_rate*100/test_times),10));

    currunt_times --;
    if (currunt_times != 0)
    {
        if(WORK_status == true)
            emit test_signals();
    }else
    {
        QMessageBox::information(this,"COMPLETE","TEST OVER!");
        RXfile.close();
        TXfile.close();
        ui->realtime_display->setText(0);
        ui->BEGIN->setText("BEGIN");
        WORK_status = false;
        correct_rate = 0;
    }
}
