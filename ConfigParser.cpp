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

IConfigContext* ConfigParser::Parser(std::vector<std::string> tokens, IConfigContext *parent)
{
	IConfigContext *root = new IConfigContext(NULL, MAIN);

	try {
		ParserRecursive(tokens_, root);
	} catch (std::exception &e) {
		std::cout << "Error: Parsing error" << std::endl;
		return (NULL);
	}
	return (root);
}

void	ConfigParser::ParserRecursive(std::vector<std::string> tokens, IConfigContext *parent)
{
	std::vector<std::string>::iterator it = tokens.begin();
	std::vector<std::string>::iterator last_it = tokens.end();
	last_it--;

	while (it != tokens.end())
	{
		int ContextType = IsContext(*it);

		if (ContextType > 0)
		{
			if (it == last_it)
				throw (ConfigParser::ConfigSyntaxError());

			int bracket_count = 0;
			std::vector<std::string> subTokens;
			IConfigContext *node = new IConfigContext(parent, ContextType);

			if (*(++it) != "{")
				throw	(ConfigParser::ConfigSyntaxError());
			bracket_count++;
			++it;
			while (it != tokens.end() && bracket_count > 0)
			{
				subTokens.push_back(*it);
				if (*it == "{")
					bracket_count++;
				if (*it == "}")
					bracket_count--;
				++it;
			}
			try {
				ParserRecursive(subTokens, node);
			} catch (std::exception &e) {
				std::cerr << e.what() << std::endl;
				return ;
			}
			if (it == tokens.end())
				return ;
		}
		else if (IsDirective(*it))
		{
			if (it == last_it)
				throw (ConfigParser::ConfigSyntaxError());
		}
		else {
			throw (ConfigParser::ConfigSyntaxError());
		}
		++it;
	}
}

int IsContext(std::string token)
{
	std::vector<std::string> ContextStrings;
	ContextStrings.push_back("main");
	ContextStrings.push_back("http");
	ContextStrings.push_back("server");
	ContextStrings.push_back("events");
	ContextStrings.push_back("location");

	for (size_t i = 0; i < ContextStrings.size(); ++i)
	{
		if (token == ContextStrings[i])
			return (static_cast<int>(i));
	}
	return (-1);
}

bool IsDirective(std::string token)
{
	std::vector<std::string> DirectiveStrings;
	DirectiveStrings.push_back("worker_processes");
	DirectiveStrings.push_back("worker_connections");
	DirectiveStrings.push_back("listen");
	DirectiveStrings.push_back("server_name");
	DirectiveStrings.push_back("root");
	DirectiveStrings.push_back("index");
	DirectiveStrings.push_back("error_page");
	DirectiveStrings.push_back("access_log");

	for (size_t i = 0; i < DirectiveStrings.size(); ++i)
	{
		if (token == DirectiveStrings[i])
			return (true);
	}
	return (false);
}

const char* ConfigParser::ConfigSyntaxError::what() const throw()
{
	return ("Error: Config file has syntax error");
}
