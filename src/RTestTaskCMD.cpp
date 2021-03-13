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
		//��֡ Ȼ�����֡�����ж�Ӧ�Ĳ���
		/*
				Ŀǰ����ô��ģ�ÿ���´����඼�ж�Ӧ��Parse������ͬʱ��Read����Write������
			Ȼ�����ûص�����֮��ֻҪÿ������ʵ�ֶ�Ӧ��Read����Write���������ص���������
			������ϸ��
		*/
		RTestTask* task = nullptr;
		if (CallBacks.find("demo") != CallBacks.end())
		{
			//��ȡ�������Ҫʲô���������ڵ�ǰ���ж��壬Ȼ����task��ʹ��cmdtaskȡ��ʹ��
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