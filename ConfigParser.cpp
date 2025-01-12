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

IConfigContext* ConfigParser::Parser(std::vector<std::string> tokens)
{
	IConfigContext *MainContext = new IConfigContext(NULL, MAIN);
	
	size_t i = 0;
	
	//이거 어떻게 할지 생각해 봐야 할듯?

	while (i < tokens.size())
	{
		if (IsContext(tokens[i]))
		{
			
		}
	}

	return (MainContext);
}

bool IsContext(std::string token)
{
	std::vector<std::string> ContextStrings = {"main", "http", "server", "events", "location"};

	for (size_t i = 0; i < ContextStrings.size(); ++i)
	{
		if (token == ContextStrings[i])
			return (true);
	}
	return (false);
}