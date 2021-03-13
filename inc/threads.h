#ifndef __THREADS_H__
#define __THREADS_H__

#include <iostream>
#include <queue>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <boost/thread/lock_factories.hpp>
#include <boost/chrono.hpp>

class RTask;
class Threads
{
public:
	Threads();
	~Threads();

	void Init();
	void Start();
	void AddTask(RTask* task);
	//作为线程的成员函数必须是静态的
	static void Main(void *arg);
	void Active();
	void Stop();

	int tid;
private:
	boost::thread this_thread;
	boost::mutex mu;
	boost::mutex task_mutex;
	boost::condition_variable_any handle;
	boost::condition_variable_any active;
	
	std::queue<RTask*> taskList;
};

#endif
