#pragma once

# include "IConfigContext.hpp"
# include "ConfigData.hpp"
# include "ConfigParser.hpp"
# include "ConfigReader.hpp"
# include <sstream>

class ConfigHandler
{
	private:
		ConfigReader reader_;
		ConfigData data_;
		ConfigParser parser_;

	public:
		ConfigHandler();
		ConfigHandler(std::string law_data);
};