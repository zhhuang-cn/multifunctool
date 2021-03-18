#ifndef __RPARSER_H__
#define __RPARSER_H__

#include <iostream>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

class RParser
{
public:
	static void GetConfig();
	static std::string GetStr(const std::string name);
	static int GetInt(const std::string name,const int defInt);

private:
	static boost::property_tree::ptree pt;
};


#endif // !__RPARSER_H__


