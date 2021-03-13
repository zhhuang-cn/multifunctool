#include "RFactory.h"
#include "RTestTaskCMD.h"
#include "RTaskTestDemo.h"

RFactory* RFactory::instance = nullptr;
RFactory  RFactory::autoClean;

RTask* RFactory::Create()
{
	RTestTaskCMD* task = new RTestTaskCMD();
	RTaskTestDemo *demo = new RTaskTestDemo();

	task->Register("demo", demo);

	return task;
}

