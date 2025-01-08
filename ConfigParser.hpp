#pragma once

# include "IConfigContext.hpp"
# include <iostream>
# include <vector>

class ConfigParser
{
	private:
		std::vector<std::string> tokens;
	
	public:
		IConfigContext	*Parsing(std::string config_data);
};