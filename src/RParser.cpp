#include "RParser.h"

using namespace std;
using namespace boost::property_tree;

boost::property_tree::ptree RParser::pt;

void RParser::GetConfig()
{
	read_ini("config.ini", pt);
}

string RParser::GetStr(const string name)
{
	string str = pt.get<string>(name);
	return str;
}

int RParser::GetInt(const string name, const int defInt)
{
	int ret;

	if (!pt.get<int>(name)) ret = defInt;
	else ret = pt.get<int>(name);
	
	return ret;
}
