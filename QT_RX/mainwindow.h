#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QFile>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    bool UART_status; // false unconnected ;  true connected
    int currunt_times;
    QSerialPort *serial;
    QSerialPortInfo *serialinfo;
    QTimer m_time;
    QFile RXfile;
    QString RXfilename;
    QString PAstatus;
    int Distance;
    int interval;
    bool recieve_status;
private slots:
    void UART_ACTION(void);
    void TimeoutAction(void);
    void serial_readData(void);
};

#endif // MAINWINDOW_H
