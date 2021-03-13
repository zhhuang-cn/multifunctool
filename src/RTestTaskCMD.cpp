#include "RTestTaskCMD.h"
#include <vector>
#include <boost\asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>

using namespace std;
using namespace boost;

void RTestTaskCMD::WriteHandler()
{
	return;
}

void RTestTaskCMD::ReadHandler(const std::string msg)
{
	cout << "recv msg -> " << msg << endl;
	return;
}

bool RTestTaskCMD::Init()
{
	this->cmdTask = this;
	this->setcb();

	int len = 0;
	//vector<char> buf(1024,0);
	char buff[1024] = { 0 };
	boost::system::error_code ec;
	for (;;)
	{
		//buf.clear();
		memset(buff, 0, sizeof(buff));
		len = sock->read_some(boost::asio::buffer(buff), ec);
		if (ec)
		{
			cout << "RTestTaskCMD::Init()" << endl;
			break;
		}
		cout << "recv data is " << buff << endl;
		//解帧 然后根据帧类别进行对应的操作
		/*
				目前是这么想的，每个新创的类都有对应的Parse函数，同时有Read或者Write函数，
			然后设置回调函数之后，只要每个类里实现对应的Read或者Write函数，隐藏调用这两个
			函数的细节
		*/
		RTestTask* task = nullptr;
		if (CallBacks.find("demo") != CallBacks.end())
		{
			//获取任务后需要什么变量可以在当前类中定义，然后在task中使用cmdtask取出使用
			task = CallBacks["demo"];
			task->cmdTask = this;
			task->sock = sock;
			task->Parse(buff);
		}
	}
	return true;
}

void RTestTaskCMD::Register(std::string type, RTestTask* task)
{
	if (type.empty() || !task) return;
	else if (CallBacks.find(type) != CallBacks.end())
	{
		cout << "Task [" << type << "] is already exit" << endl;
		return;
	}

	CallBacks[type] = task;
}
//
//void RTestTaskCMD::Read()
//{
//
//}