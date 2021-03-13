#ifndef __PROGRAMING_H__
#define __PROGRAMING_H__

#include <QtWidgets/QWidget>
#include <QApplication>
#include <qserialport.h>
#include <qserialportinfo.h>
#include <qmessagebox.h>
#include <qtimer.h>

#include <boost/shared_ptr.hpp>

#include <iostream>
#include <string>

#include "ui_programing.h"
class programing : public QWidget
{
	Q_OBJECT
public:
	programing(QWidget *parent = 0);;
	~programing();
	//function
	void ResetDisplayWindows();
	void SetSerial(boost::shared_ptr<QSerialPort> serialPort);

private slots:
	void fileChooseBtn_onClicked();
	void CheckComBtn_onClicked();
	void ProgramBtn_onClicked();
	void ReadSlot();
	void Handle();

private:
	const QString m_grey_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:grey";
	const QString m_red_SheetStyle = "min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;background:red";

	Ui_Form ui;
	std::string filePath;
	bool isStarted;
	boost::shared_ptr<QSerialPort> serialPort;
	boost::shared_ptr<QMessageBox> message;
	boost::shared_ptr<QTimer>      timer;
	QByteArray info;

	//串口默认参数
	int BaudRate;
	int DataBit;
	int StopBit;
	bool Parity;
};

#endif
