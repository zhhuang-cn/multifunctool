#include <qmovie.h>

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/system/error_code.hpp>

#include "multifunctool.h"
#include "programing.h"
#include "threadpool.h"
#include "RFactory.h"
#include "RTask.h"
#include "RParser.h"


#define  THREAD_CREATE_NUM  10
#define  LISTEN_PORT		32000

using namespace boost;

multifunctool::multifunctool(QWidget *parent): QMainWindow(parent),\
    m_acceptor(m_io, endpoint_type(asio::ip::tcp::v4(), RParser::GetInt("NETWORK.listen", LISTEN_PORT))), \
    closeLoad(new QTimer(this))
{
    ui.setupUi(this);

	//参数初始化
	isStoped = false;

	load = new Loading(this);
	load->start();
	closeLoad->start(3000);

	//函数初始化
	InitDisplayWindows();
	ThreadPool::Get()->Create(RParser::GetInt("NETWORK.thread_num",THREAD_CREATE_NUM));				//线程池创建


	//按钮属性初始化
	ui.close_btn->setDisabled(true);
	ui.connect_btn->setDisabled(false);

	//信号槽
	connect(ui.close_btn, SIGNAL(clicked()), this, SLOT(closeBtn_onClicked()));
	connect(ui.connect_btn, SIGNAL(clicked()), this, SLOT(connectBtn_onClicked()));
	connect(ui.load_img_btn, SIGNAL(clicked()), this, SLOT(loadBtn_onClicked()));
	connect(closeLoad.get(), SIGNAL(timeout()), this, SLOT(loadingClose()));
}

void multifunctool::loadingClose()
{
	delete load;
	//修改bug，定时器会再次进入该函数，导致重复释放指针
	closeLoad->stop();
}

multifunctool::~multifunctool() {}

void multifunctool::InitDisplayWindows()
{
	DisCotainer.push_back(ui.tw1);
	DisCotainer.push_back(ui.tw2);
	DisCotainer.push_back(ui.tw3);
	DisCotainer.push_back(ui.tw4);
	DisCotainer.push_back(ui.tw5);
	DisCotainer.push_back(ui.tw6);
	DisCotainer.push_back(ui.tw7);
	DisCotainer.push_back(ui.tw8);
	DisCotainer.push_back(ui.tw9);
	DisCotainer.push_back(ui.tw10);
	DisCotainer.push_back(ui.tw11);
	DisCotainer.push_back(ui.tw12);
	ResetDisplayWindows();
}

void multifunctool::ResetDisplayWindows()
{
	QStringList header;
	header << "Content";
	for (auto& tablewidget : DisCotainer)
	{
		tablewidget->setColumnCount(1);
		tablewidget->setHorizontalHeaderLabels(header);
		tablewidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		tablewidget->setRowCount(12);
		tablewidget->show();
	}
}

void multifunctool::closeBtn_onClicked()
{
	ui.close_btn->setDisabled(true);
	ui.connect_btn->setDisabled(false);

	ThreadPool::Get()->stopAll();
	m_io.stop();
	isStoped = true;
}

void multifunctool::connectBtn_onClicked()
{
	ui.close_btn->setDisabled(false);
	ui.connect_btn->setDisabled(true);

	boost::thread lt(boost::bind(multifunctool::Accept, this));	//监听线程创建
	isStoped = false;
	m_io.run();
}

void multifunctool::Accept(void* arg)
{
	try {
		multifunctool* t = (multifunctool*)arg;
		while (true)
		{
			sock_ptr sock(new socket_type(t->m_io));
			t->m_acceptor.accept(*sock);
			if (t->isStoped) break;

			RTask* task = RFactory::Get()->Create();
			task->sock = sock;
			ThreadPool::Get()->Active(task);
		}
	}
	catch (...)
	{
		std::cout << "Accept Error" << std::endl;
	}

}

void multifunctool::loadBtn_onClicked()
{
	programing* p = new programing();
	p->show();
}
