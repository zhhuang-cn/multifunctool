#ifndef __MULTIFUNCTO0L_H__
#define __MULTIFUNCTO0L_H__

#include <iostream>
#include <vector>
#include <boost/asio.hpp>

#include <QtWidgets/QMainWindow>
#include <qtablewidget.h>
#include <QTimer>
#include "loadCatoon.h"
#include "ui_multifunctool.h"

class multifunctool : public QMainWindow
{
    Q_OBJECT
    typedef boost::asio::ip::tcp::socket	socket_type;
    typedef boost::asio::ip::tcp::endpoint	endpoint_type;
    typedef boost::asio::ip::tcp::acceptor	acceptor_type;
    typedef boost::shared_ptr<socket_type>  sock_ptr;
public:
    multifunctool(QWidget *parent = Q_NULLPTR);
	~multifunctool();
private slots:
    void closeBtn_onClicked();
    void connectBtn_onClicked();
    void loadBtn_onClicked();

    void loadingClose();

private:
	//function
	void InitDisplayWindows();
	void ResetDisplayWindows();

	static void Accept(void* arg);
	//void accept_handler(const boost::system::error_code &ec, sock_ptr sock);

	//charater
	std::vector<QTableWidget*> DisCotainer;

	boost::asio::io_service m_io;
	acceptor_type m_acceptor;

	bool isStoped;

	Loading* load;
	boost::shared_ptr<QTimer> closeLoad;

	//not use
	unsigned int devNum;
	unsigned int comChoice;
private:
    Ui::multifunctool ui;
};

#endif