#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

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
    bool WORK_status; // false unworked ; true working
    QSerialPort *serial;
    QSerialPortInfo *serialinfo;
    void writeData(const QByteArray &data);
private slots:
    void UART_ACTION(void);
    void serial_readData(void);
    void BEGIN_ACTION(void);
};

#endif // MAINWINDOW_H
