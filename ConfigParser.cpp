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

std::vector<std::string> ConfigParser::GetTokens()
{
	return (tokens_);
}

IConfigContext* ConfigParser::Parser(std::vector<std::string> tokens, IConfigContext *parent)
{
	std::vector<std::string>::iterator it = tokens.begin();
	std::vector<std::string>::iterator last = tokens.end();
	--last;

	while (it != tokens.end())
	{
		int context_type = IsContext(*it);
		if (context_type > 0)
		{
			std::cout << "Token : " << *it << std::endl;
			if (*it == *last)
				throw (ConfigParser::ConfigSyntaxError(NULL));
			if (*(++it) != "{")
				throw (ConfigParser::ConfigSyntaxError(NULL));

			std::vector<std::string> sub_tokens;
			int	bracket_count = 1;
			IConfigContext *node = new IConfigContext(parent, context_type);

			++it;
			while (it != tokens.end() && bracket_count > 0)
			{
				if (*it == "{")
					bracket_count++;
				if (*it == "}")
					bracket_count--;
				sub_tokens.push_back(*it);
				++it;
			}
			if (bracket_count == 0)
				Parser(sub_tokens, node);
			if (bracket_count > 0)
				throw (ConfigParser::ConfigSyntaxError(node));
		}
		else if (IsDirective(*it))
		{
			std::cout << "direc : " << *it << std::endl;
			if (*it == *last)
				throw (ConfigParser::ConfigSyntaxError(NULL));

			std::string directive_key = *it;
			++it;
			std::string::iterator str_it_end = (*it).end();
			str_it_end--;
			while (*it != ";" && *str_it_end != ';')
			{
				str_it_end = (*it).end();
				str_it_end--;
				parent->AddDirectives(directive_key, *it);
				++it;
			}
			if ((*it).size() != 1 && *str_it_end == ';')
			{
				std::string value = (*it).substr(0, (*it).size() - 2);
				parent->AddDirectives(directive_key, value);
			}
			std::cout << "token ? : " << *it << std::endl;
		}
		else
		{
			throw (ConfigParser::ConfigSyntaxError(NULL));
		}
		++it;
	}
	return (parent);
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

ConfigParser::ConfigSyntaxError::ConfigSyntaxError(IConfigContext *node)
{
	if (node != NULL)
		delete (node);
}