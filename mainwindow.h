#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QByteArray>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_show_ports_clicked();

    void on_open_port_clicked();

    void on_btn_send_clicked();

    void populateBaudRate();

    void on_btn_Disconnect_clicked();

private:
    Ui::MainWindow *ui;
    void loadPorts();
    QSerialPort * _serialport;
    QByteArray _dataBuff;
    void readData();
    QString convertStopBits(QSerialPort::StopBits stopbit);
    QString convertParityBits(QSerialPort::Parity parityBits);
};
#endif // MAINWINDOW_H
