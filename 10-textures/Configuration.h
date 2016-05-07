#ifndef __CONFIGURATION_H
#define __CONFIGURATION_H

#include <string>
#include <map>

class Configuration
{
public:
	static Configuration* getInstance(void);
	void load(std::string filename);
	std::string getConfiguration(const std::string key);

private:
	Configuration(void);

private:
	std::map<std::string, std::string> settings;
};

#endif