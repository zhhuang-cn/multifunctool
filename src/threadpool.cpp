#include "threadpool.h"
#include "threads.h"
#include "RTask.h"

#include <boost/thread.hpp>

ThreadPool* ThreadPool::instance = nullptr;
ThreadPool m_cleanup;

using namespace boost;

int ThreadPool::Create(int thread_num)
{
	int i;
	this->thread_num = thread_num;
	this->last_tid = -1;
	for (i = 0; i < thread_num; ++i)
	{
		shared_ptr<Threads> ptr(new Threads());
		ptr->tid = i + 1;
		ptr->Start();
		threadpools.push_back(ptr);
	}
	return i;
}

void ThreadPool::stopAll()
{
	std::cout << "ThreadPool::stopAll()" << std::endl;
	for (auto &x : threadpools)
	{
		x->Stop();
	}
}

void ThreadPool::Active(RTask* task)
{
	int tid = (last_tid + 1) % thread_num;
	last_tid = tid;
	shared_ptr<Threads> t = threadpools[tid];

	t->AddTask(task);
	t->Active();
}

