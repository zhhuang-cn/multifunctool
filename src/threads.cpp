#include "threads.h"
#include "RTask.h"
#include <boost\thread.hpp>

Threads::Threads():this_thread(boost::bind(Threads::Main, this))
{
	Start();
}
Threads::~Threads(){}

using namespace boost;

void Threads::AddTask(RTask* task)
{
	if (!task) return;

	lock_guard<mutex> mu(task_mutex);
	taskList.push(task);
}

void Threads::Active()
{
	handle.notify_one();
}

void Threads::Init() 
{

}

void Threads::Stop()
{
	//std::cout << tid << " thread Stop()" << std::endl;
	this_thread.interrupt();
}

void Threads::Start()
{
	std::cout << tid << " thread Start" << std::endl;
	Init();
	thread th(boost::bind(Threads::Main, this));

	//detach之后线程所属独立，随主进程终结而终结，此时按钮去控制不可控
	//this_thread.detach();
}

void Threads::Main(void *arg)
{

	Threads* t = (Threads*)arg;
	try {
		while (1)
		{
			{
				auto lock = make_unique_lock(t->mu);
				t->handle.wait(lock);

				RTask* task = nullptr;
				{
					lock_guard<mutex> mu(t->task_mutex);
					if (t->taskList.size())
					{
						task = t->taskList.front();
						t->taskList.pop();
						task->Init();
					}
				}
				
			}
		}
	}
	catch (const thread_interrupted)
	{
		std::cout << t->tid << "interrupt" << std::endl;
	}
}

