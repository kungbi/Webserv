#pragma once

# include "IConfigContext.hpp"
# include <vector>
# include <sstream>
# include <stdexcept>


class ConfigParser
{
	private:
		std::vector<std::string> tokens_;
	
	public:
		void Tokenize(std::string config_data);
		IConfigContext *Parser(std::vector<std::string> tokens, IConfigContext *root);
		std::vector<std::string> GetTokens();

	class ConfigSyntaxError : public std::exception
	{
		public:
			ConfigSyntaxError(IConfigContext *node);
			virtual const char* what() const throw();
	};
};