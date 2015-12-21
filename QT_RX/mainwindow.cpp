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
    recieve_status = false;
    QStringList comlist;
    QStringList PAlist;
    comlist<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"<<"COM7"<<"COM8";
    PAlist<<"None"<<"3dbi"<<"5dbi";
    ui->UART_com_num->addItems(comlist);
    ui->PAstatus->addItems(PAlist);
    connect(ui->UART_connect_button,SIGNAL(clicked()),this,SLOT(UART_ACTION()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_readData()));//UART recieve data
    interval = 2000;

    //connect(ui->BEGIN,SIGNAL(clicked()),this,SLOT(BEGIN_ACTION()));
    //connect(this,SIGNAL(test_signals()),this,SLOT(test_once()));
    connect(&m_time,SIGNAL(timeout()),SLOT(TimeoutAction()));
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
void MainWindow::serial_readData(void)
{
    if(recieve_status == false)
    {
        recieve_status = true;
        Distance = ui->Distance->value();
        PAstatus = ui->PAstatus->currentText();
        char cdistance[10];
        QString sdistance;
        sprintf_s(cdistance,"%d",Distance);
        sdistance = cdistance;
        QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
        RXfilename = time.toString("yyyy-MM-dd_hh-mm-ss"); //设置显示格式
        RXfilename+="_dt"+sdistance+"_PA"+PAstatus+".txt";
        RXfile.setFileName(RXfilename);
        if(!RXfile.open(QFile::WriteOnly |QIODevice::Truncate)){
            QMessageBox::warning(this,"RXFile","RXFile cannot open!");
        }else
        {
            //QMessageBox::warning(this,"Begin","Begin to recieve data!");
            m_time.start(interval/2);
        }
    }else{
        m_time.start(interval/2);
    }
}
void MainWindow::TimeoutAction(void)
{
    m_time.stop();
    QByteArray data = serial->readAll();
    QTextStream RXout(&RXfile);
    for(int i=0;i<data.length();i++)
    {
        RXout<<data[i];
    }
    RXout<<"\n";
    currunt_times=data[1];
    char ccurrunt_times[10];
    sprintf_s(ccurrunt_times,"%d",currunt_times);
    ui->realtime_display->setText(ccurrunt_times);
    if (currunt_times == 1)
    {
        RXfile.close();
        QMessageBox::information(this,"COMPLETE","Recieve Over!");
        recieve_status = false;
        ui->realtime_display->setText(0);
    }
}
