#ifndef __RTASK_H__
#define __RTASK_H__

#include <boost\asio.hpp>
#include <boost/shared_ptr.hpp>

class RTask
{
public:
	virtual bool Init() = 0; //����ĳ�ʼ��
	boost::shared_ptr<boost::asio::ip::tcp::socket> sock; //ͨ�ŵ�sock


	RTask() {}
	~RTask() {}
};

#endif // !__RTASK_H__


