#pragma once

# include <fstream>
# include <iostream>

class ConfigReader
{
	private:
		std::string default_conf_path;

	public:
		ConfigReader();

		std::string readConfigFile(std::string filepath);
		std::string getDefaultPath();
};