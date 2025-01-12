#pragma once

# include "IConfigContext.hpp"
# include <iostream>
# include <vector>
# include <sstream>

class ConfigParser
{
	private:
		std::vector<std::string> tokens_;
	
	public:
		void Tokenize(std::string config_data);
		IConfigContext *ConfigParser::Parser(std::vector<std::string> tokens);
};