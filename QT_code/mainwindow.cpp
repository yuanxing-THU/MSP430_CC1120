#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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
    comlist<<"COM1"<<"COM2"<<"COM3"<<"COM4"<<"COM5"<<"COM6"<<"COM7"<<"COM8";
    ui->UART_com_num->addItems(comlist);
    connect(ui->UART_connect_button,SIGNAL(clicked()),this,SLOT(UART_ACTION()));
    connect(serial, SIGNAL(readyRead()), this, SLOT(serial_readData()));
    connect(ui->BEGIN,SIGNAL(clicked()),this,SLOT(BEGIN_ACTION()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::UART_ACTION(void)
{
    if(UART_status == false )
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
    else
    {
        //close UART
        serial->close();
        ui->UART_connect_button->setText("CONNECT");
        UART_status = false;
        ui->serial_status->setText(tr("Disconnected!"));
    }
}
void MainWindow::serial_readData(void)
{

}
void MainWindow::BEGIN_ACTION(void)
{
    if(WORK_status == false)
    {
        WORK_status = true;
    }else
    {
        WORK_status = false;
    }
}
void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}
