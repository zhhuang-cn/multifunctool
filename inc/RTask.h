#ifndef __RTASK_H__
#define __RTASK_H__

#include <boost\asio.hpp>
#include <boost/shared_ptr.hpp>

class RTask
{
public:
	virtual bool Init() = 0; //任务的初始化
	boost::shared_ptr<boost::asio::ip::tcp::socket> sock; //通信的sock


	RTask() {}
	~RTask() {}
};

#endif // !__RTASK_H__


