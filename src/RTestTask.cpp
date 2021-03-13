#include "RTestTask.h"

#include <boost/asio/buffer.hpp>

using namespace boost;

void RTestTask::Read()
{
	boost::system::error_code ec;
	while (true)
	{
		memset(buff, 0, sizeof(buff));
		sock->read_some(boost::asio::buffer(buff), ec);
		if (ec)
		{
			std::cout << "Read Error" << std::endl;
			break;
		}
		readFunc(buff, ec);
	}
}

void RTestTask::Write(const std::string msg)
{
	boost::system::error_code ec;
	//sock->async_write_some(boost::asio::buffer("123"),boost::bind(&WriteCB, boost::asio::placeholders::error));
	sock->write_some(boost::asio::buffer(msg));
	writeFunc(ec);
}

void RTestTask::setcb() {
	readFunc = boost::bind(&RTestTask::ReadCB, this, _1, _2);;
	writeFunc = boost::bind(&RTestTask::WriteCB, this, boost::asio::placeholders::error);;
}

void RTestTask::ReadCB(const std::string msg, const boost::system::error_code& ec)
{
	if (ec)
	{
		std::cout << "Read Call Back Function Error" << std::endl;
		return;
	}
	this->ReadHandler(msg);
}

void RTestTask::WriteCB(const boost::system::error_code& ec)
{
	if (ec)
	{
		std::cout << "Write Call Back Function Error" << std::endl;
		return;
	}
	this->WriteHandler();
}
