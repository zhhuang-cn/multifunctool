#include "programing.h"
#include <qfiledialog.h>
#include <qtextcodec.h>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace boost::filesystem;
#pragma execution_character_set("utf-8")

programing::programing(QWidget *parent) : QWidget(parent), \
	//初始化列表初始参数
	serialPort(new QSerialPort(this)), \
	message(new QMessageBox(this)), \
	timer(new QTimer(this))
{
	ui.setupUi(this);

	//参数初始化
	isStarted = false;
	
	//函数及控件初始化
	setWindowTitle(QString("LoadProgram"));
	ui.led->setStyleSheet(m_grey_SheetStyle);
	ResetDisplayWindows();
	//信号槽
	connect(ui.fileChooseBtn, SIGNAL(clicked()), this, SLOT(fileChooseBtn_onClicked()));
	connect(ui.CheckComBtn, SIGNAL(clicked()), this, SLOT(CheckComBtn_onClicked()));
	connect(ui.ProgramBtn, SIGNAL(clicked()), this, SLOT(ProgramBtn_onClicked()));
	connect(serialPort.get(), SIGNAL(readyRead()), this, SLOT(ReadSlot()));
	connect(timer.get(), SIGNAL(timeout()), this, SLOT(Handle()));
}


programing::~programing()
{
}

void programing::fileChooseBtn_onClicked()
{
	QFileDialog *file = new QFileDialog(this);

	file->setDirectory(QString::fromStdString(current_path().string()));
	QString filePath;
	if (file->exec()) {
		filePath = file->getOpenFileName();
		this->filePath = filePath.toStdString();
	}
}

void programing::ResetDisplayWindows()
{
	QStringList header;
	header << "Content";
	ui.mainScreen->setColumnCount(1);
	ui.mainScreen->setHorizontalHeaderLabels(header);
	ui.mainScreen->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.mainScreen->setRowCount(18);
	ui.mainScreen->show();
	
}

void programing::CheckComBtn_onClicked()
{
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
		if (ui.ComSelect->findText(info.portName()) == -1) {
			ui.ComSelect->addItem(info.portName());
		}
	}
}

void programing::ProgramBtn_onClicked()
{
	isStarted = !isStarted;
	if (isStarted)
	{
		if (serialPort->isOpen())
			serialPort->close();
		SetSerial(serialPort);
		if (!serialPort->open(QIODevice::ReadWrite))
		{
			message->setText("串口打开失败，请检查！");
			message->exec();
		}
	}
	else
	{
		if (serialPort->isOpen())
			serialPort->close();
	}
	ui.ProgramBtn->setText(isStarted ? QString("烧录结束") : QString("烧录开始"));
}

void programing::SetSerial(shared_ptr<QSerialPort> serialPort)
{
	QString BaudRate = ui.BaudSelect->currentText();
	QString DataBit	 = ui.bitSelect->currentText();
	int StopBit = ui.StopSelect->currentIndex();
	int Parity = ui.ParSelect->currentIndex();

	std::cout << BaudRate.toStdString() << " " << DataBit.toStdString() << " " << StopBit << " " << Parity << std::endl;

	switch (boost::lexical_cast<int>(BaudRate.toStdString()))
	{
	case 9600:
		serialPort->setBaudRate(QSerialPort::Baud9600);
		break;
	case 19200:
		serialPort->setBaudRate(QSerialPort::Baud19200);
		break;
	case 38400:
		serialPort->setBaudRate(QSerialPort::Baud38400);
		break;
	case 115200:
		serialPort->setBaudRate(QSerialPort::Baud115200);
		break;
	}

	switch (boost::lexical_cast<int>(DataBit.toStdString()))
	{
	case 5:
		serialPort->setDataBits(QSerialPort::Data5);
		break;
	case 6:
		serialPort->setDataBits(QSerialPort::Data6);
		break;
	case 7:
		serialPort->setDataBits(QSerialPort::Data7);
		break;
	case 8:
		serialPort->setDataBits(QSerialPort::Data8);
		break;
	}

	switch (Parity)
	{
	case 0:
		serialPort->setParity(QSerialPort::NoParity);
		break;
	case 1:
		serialPort->setParity(QSerialPort::OddParity);
		break;
	case 2:
		serialPort->setParity(QSerialPort::EvenParity);
		break;
	}

	switch (StopBit)
	{
	case 0:
		serialPort->setStopBits(QSerialPort::OneStop);
		break;
	case 1:
		serialPort->setStopBits(QSerialPort::OneAndHalfStop);
		break;
	case 2:
		serialPort->setStopBits(QSerialPort::TwoStop);
		break;
	}

	serialPort->setFlowControl(QSerialPort::NoFlowControl);
	serialPort->setPortName(ui.ComSelect->currentText());
}

void programing::ReadSlot()
{
	timer->start(1000);
	info.append(serialPort->readAll());
}

void programing::Handle()
{
	timer->stop();
	std::cout << info.data() << std::endl;
	
}