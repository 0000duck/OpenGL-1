#include "Configuration.h"
#include <fstream>
#include <sstream>
#include <string>

Configuration::Configuration(void)
{
}

Configuration* Configuration::getInstance(void)
{
	static Configuration c;
	return &c;
}

void Configuration::load(std::string filename)
{
	std::string str;
	std::ifstream file(filename);
	while(std::getline(file,str)) {
		if(str.at(0) == '#')
			continue;
		std::string key;
		std::string value;
		std::stringstream iss;
		iss << str;
		std::getline(iss, key,' ');
		std::getline(iss, value);
		settings.insert(std::pair<std::string, std::string>(key, value));
	}
	file.close();
}

std::string Configuration::getConfiguration(const std::string key)
{
	return settings[key];
}