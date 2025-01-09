#include "ConfigParser.hpp"

void ConfigParser::Tokenize(std::string config_data)
{
	std::stringstream ss(config_data);
	std::string token;

	while (ss >> token)
	{
		tokens_.push_back(token);
	}
}

template <typename DirectiveType>
IConfigContext<DirectiveType>* ConfigParser::Parser(std::vector<std::string> tokens)
{
	size_t	i = 0;

	while (i < tokens.size())
	{
		if (tokens[i])
	}
}