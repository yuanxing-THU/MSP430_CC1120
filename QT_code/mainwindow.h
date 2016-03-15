#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTimer>
#include <QFile>
#include <vector>
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
    int test_times; // the test times in a cycle;
    int cycle_times; // the cycle times
    int currunt_times;
    int currunt_cycle;
    int message_length;
    QSerialPort *serial;
    QSerialPortInfo *serialinfo;
    void writeData(const QByteArray &data);
    QTimer m_time;
    QFile TXfile;
    QFile RXfile;
    QFile crfile;
    QString TXfilename;
    QString RXfilename;
    QString PAstatus;
    int Distance;
    int interval;
    QByteArray txdata;
    int correct_rate;
    QByteArray rxdata;
    std::vector<int> correctratio;
signals:
    void test_signals();
private slots:
    void UART_ACTION(void);
    void BEGIN_ACTION(void);
    void test_once(void);
    void TimeoutAction(void);
    bool create_file(void);
};

#endif // MAINWINDOW_H
