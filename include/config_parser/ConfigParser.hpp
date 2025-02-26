#pragma once

#include "IConfigContext.hpp"
#include "IConfigDirective.hpp"
#include <vector>
#include <sstream>
#include <stdexcept>

class ConfigParser
{
	private:
		std::vector<std::string> configTokens_;
		void parseConfigRecursive(std::vector<std::string> configTokens, IConfigContext* parentContext);

	public:
		void tokenize(std::string config_data);
		IConfigContext* parseConfig();

	class ConfigSyntaxError : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
};