#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>

class RTask;
class Threads;
class ThreadPool {
public:
	static ThreadPool* Get()
	{
		if (instance == nullptr)
		{
			instance = new ThreadPool();
		}
		return instance;
	}
	void Active(RTask* task);
	int Create(int thread_num);
	void stopAll();
	class AutoCleanup {
		~AutoCleanup() {
			if (ThreadPool::instance)
			{
				delete ThreadPool::instance;
				ThreadPool::instance = nullptr;
			}
		}
	};

private:

	static ThreadPool* instance;
	static ThreadPool m_cleanup;
	int thread_num;
	int last_tid;
	std::vector<boost::shared_ptr<Threads>> threadpools;
};

#endif // !__THREADPOOL_H__
