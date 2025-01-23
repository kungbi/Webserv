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

IConfigContext* ConfigParser::Parser()
{
	IConfigContext *root = new IConfigContext(NULL, MAIN);

	try {
		ParserRecursive(tokens_, root);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		DeleteTree(root);
		return (NULL);
	}
	return (root);
}

void	ConfigParser::ParserRecursive(std::vector<std::string> tokens, IConfigContext *parent)
{
	std::vector<std::string>::iterator it = tokens.begin();
	std::vector<std::string>::iterator last_it = tokens.end();

	last_it--;
	if (it == last_it) {
		throw (ConfigParser::ConfigSyntaxError());
	}
	while (it != tokens.end())
	{
		int contextType = IsContext(*it);
		int directiveType = IsDirective(*it);
		if (contextType != -1 && directiveType == -1)
		{
			if (*(++it) != "{") {
				throw (ConfigParser::ConfigSyntaxError());
			}

			if (it == last_it) {
				throw (ConfigParser::ConfigSyntaxError());
			}

			int BracketCount = 1;
			std::vector<std::string> SubTokens;
			IConfigContext* node = new IConfigContext(parent, contextType);
			
			while (it != tokens.end())
			{
				++it;
				if (it == tokens.end())
					throw (ConfigParser::ConfigSyntaxError());
				if (*it == "{")
					BracketCount++;
				if (*it == "}")
					BracketCount--;
				if (BracketCount == 0)
					break ;
				SubTokens.push_back(*it);
			}
			//*it = }
			if (BracketCount != 0)
				throw (ConfigParser::ConfigSyntaxError());
			try {
				ParserRecursive(SubTokens, node);
			} catch (...) {
				throw (ConfigParser::ConfigSyntaxError());
			}
		}
		else if (directiveType != -1 && contextType == -1)
		{
			//*it = 지시어 토큰
			if (it == last_it)
				throw (ConfigParser::ConfigSyntaxError());

			std::string DirectiveStr = *it;
			IConfigDirective *directive = new IConfigDirective(parent, directiveType);
			++it;

			while (it != tokens.end() && *it != ";")
			{
				std::string::iterator TokenIterEnd = it->end();

				--TokenIterEnd;
				if (*TokenIterEnd == ';') {
					directive->AddValue(it->substr(0, it->size() - 1));
					break ;
				}
				directive->AddValue(*it);
				++it;
			}
			parent->AddDirectives(directive);
		}
		else if (directiveType == -1 && contextType == -1) {
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
			return (i);
	}
	return (-1);
}

const char* ConfigParser::ConfigSyntaxError::what() const throw()
{
	return ("Error: Config file has syntax error");
}
