#ifndef __RTASKTESTDEMO_H__
#define __RTASKTESTDEMO_H__

#include "RTestTask.h"
class RTaskTestDemo : public RTestTask
{
public:
	void ReadHandler(const std::string msg);
	void Parse(const std::string msg);

	RTaskTestDemo();
	~RTaskTestDemo();
};

#endif

