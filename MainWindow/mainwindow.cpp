#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,_serialport(nullptr)


{
    ui->setupUi(this);
    setWindowTitle("Serial App");
    loadPorts();
    populateBaudRate();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_show_ports_clicked()
{
    for(const auto & ports: QSerialPortInfo::availablePorts())
    {
        qDebug()<< ports.portName();
    }
}

void MainWindow::loadPorts()
{
    for(const auto & ports: QSerialPortInfo::availablePorts())
    {
        ui->Comports->addItem(ports.portName());
    }

}


void MainWindow::on_open_port_clicked()
{
    if(_serialport != nullptr)
    {
        _serialport->close();
        delete _serialport;
    }
    _serialport = new QSerialPort(this);
    _serialport->setPortName(ui->Comports->currentText());
   // _serialport->setBaudRate(QSerialPort::BaudRate::Baud115200);
    _serialport->setBaudRate(ui->BaudRateBox->currentData().toInt());
    qDebug() << "BaudRate:";
    qDebug() << ui->BaudRateBox->currentData().toInt();
    // _serialport->setDataBits(QSerialPort::Data8);
    // _serialport->setParity(QSerialPort::NoParity);
    // _serialport->setStopBits(QSerialPort::OneStop);
    _serialport->setDataBits(static_cast<QSerialPort::DataBits>(ui->DataBits_CombBox->currentData().toInt()));
    _serialport->setParity(static_cast<QSerialPort::Parity>(ui->ParityBit_Comb_Box->currentData().toInt()));
    _serialport->setStopBits(static_cast<QSerialPort::StopBits>(ui->StopBitComb_Box->currentData().toInt()));
    if(_serialport->open(QIODevice::ReadWrite))
    {
        ui->lb_Btn_Status->setText("Connected");
        QMessageBox::information(this,"portStatus" , "port opened successfully");
        connect(_serialport,&QSerialPort::readyRead,this,&MainWindow::readData);

    }
    else
    {
        QMessageBox::critical(this,"Port Error","Can't open port");
    }
}


void MainWindow::on_btn_send_clicked()
{
    if(!_serialport->isOpen())
    {
        QMessageBox::critical(this,"port status","can't open port");
        return;
    }
    //
    _serialport->write(ui->line_message->text().toUtf8() + "\n");
}

void MainWindow::readData()
{
    if(!_serialport->isOpen())
    {
        QMessageBox::critical(this,"port status","can't open port");
        return;
    }
    //
    auto data = _serialport->readAll();
    qDebug()<< data;
    ui->lst_data->addItem(QString(data));
}

QString MainWindow::convertStopBits(QSerialPort::StopBits stopbit)
{
    switch (stopbit) {
    case QSerialPort::StopBits::OneStop :
        return "OneStopBit";
        break;
    case QSerialPort::StopBits::OneAndHalfStop :
        return "OneAndHalfStopBits";
        break;
    case QSerialPort::StopBits::TwoStop :
        return "TwoStopBits";
        break;
    default:
        return "Unknown";
        break;
    }

}

QString MainWindow::convertParityBits(QSerialPort::Parity parityBits)
{
    switch (parityBits) {
    case QSerialPort::Parity::NoParity :
        return "NoParity";
        break;
    case QSerialPort::Parity::OddParity :
        return "OddParity";
        break;
    case QSerialPort::Parity::EvenParity :
        return "EvenParity";
        break;
    case QSerialPort::Parity::SpaceParity :
        return "SpaceParity";
        break;
    default:
        return "Unknown";
        break;
    }

}

void MainWindow::populateBaudRate()
{
    //QList
    QList<QSerialPort::BaudRate> baudRateVal = {
        QSerialPort::BaudRate::Baud115200,
        QSerialPort::BaudRate::Baud57600,
        QSerialPort::BaudRate::Baud4800,
        QSerialPort::BaudRate::Baud9600
};
    QList<QSerialPort::DataBits> dataBitsNums = {
        QSerialPort::DataBits::Data8,
        QSerialPort::DataBits::Data5,
        QSerialPort::DataBits::Data6,
        QSerialPort::DataBits::Data7
    };
    QList<QSerialPort::StopBits> dataStopBits = {
        QSerialPort::StopBits::OneStop,
        QSerialPort::StopBits::OneAndHalfStop,
        QSerialPort::StopBits::TwoStop,

    };
    QList<QSerialPort::Parity> dataParityBits ={
        QSerialPort::Parity::NoParity,
        QSerialPort::Parity::OddParity,
        QSerialPort::Parity::EvenParity,
        QSerialPort::Parity::SpaceParity
};


    for(auto &curBaudRate : baudRateVal)
    {
        QString curBaudRate_str = QString::number(curBaudRate);
        ui->BaudRateBox->addItem("BaudRate: "+curBaudRate_str, curBaudRate);
    }

    for(const auto &dataBits: dataBitsNums)
    {
        ui->DataBits_CombBox->addItem("Data: "+QString::number(dataBits) ,dataBits);
    }

    for(const auto &dataStopBit: dataStopBits)
    {
        ui->StopBitComb_Box->addItem(convertStopBits(dataStopBit) ,dataStopBit);
    }

    for(const auto &dataParityBit: dataParityBits)
    {
        ui->ParityBit_Comb_Box->addItem(convertParityBits(dataParityBit) ,dataParityBit);
    }
}

void MainWindow::on_btn_Disconnect_clicked()
{
    if(_serialport != nullptr)
    {
        _serialport->close();
        delete _serialport;
        qDebug()<<"Button Disconnected";
        ui->lb_Btn_Status->setText("Disconnected");
        QMessageBox::information(this,"portStatus", "Port " +ui->Comports->currentText() + "Disconnected Successfully..");

    }
}

