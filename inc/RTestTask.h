#ifndef __RTESTTASK_H__
#define __RTESTTASK_H__

#include <boost\system\error_code.hpp>
#include <boost\function.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <string>

#include "RTask.h"
class RTestTask : public RTask
{
	typedef boost::function<void(const std::string, const boost::system::error_code&)> ReadFunc;
	typedef boost::function<void(const boost::system::error_code& ec)> WriteFunc;
public:
	//character
	RTestTask *cmdTask = 0;


	//function
	virtual bool Init() { return true; }
	virtual void Parse(const std::string msg) {}

	virtual void ReadCB(const std::string msg, const boost::system::error_code& ec);
	virtual void WriteCB(const boost::system::error_code& ec);

	virtual void ReadHandler(const std::string msg) {}
	virtual void WriteHandler() {}

	virtual void Read();
	virtual void Write(const std::string msg);
	void setcb();

	RTestTask() = default;
	~RTestTask() = default;

	/*virtual void WriteCB(const boost::system::error_code& ec);
	virtual void ReadCB(const std::string msg, const boost::system::error_code& ec);*/


protected:
	
	ReadFunc readFunc = boost::bind(&RTestTask::ReadCB, this, _1, _2);
	WriteFunc writeFunc = boost::bind(&RTestTask::WriteCB, this, boost::asio::placeholders::error);

	char buff[1024];
};


#endif // !__RTESTTASK_H__


