#ifndef __RTESTTASKCMD_H__
#define __RTESTTASKCMD_H__

#include <iostream>
#include <string>
#include <map>

#include "RTestTask.h"
class RTestTaskCMD : public RTestTask
{
public:

	virtual bool Init();
	void WriteHandler();
	void ReadHandler(const std::string msg);
	//virtual void Read();
	virtual void Register(std::string type, RTestTask* task);

	RTestTaskCMD() {}
	~RTestTaskCMD() {}

private:
	std::map<std::string, RTestTask*> CallBacks;
};


#endif // !__RTESTTASK_CMD_H__


