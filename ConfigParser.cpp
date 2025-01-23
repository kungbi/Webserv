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
		ContextType contextType = IsContext(*it);
		if (contextType != ContextType::END)
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
		DirectiveType directiveType = IsDirective(*it);
		if (directiveType != DirectiveType::END)
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
		else {
			throw (ConfigParser::ConfigSyntaxError());
		}
		++it;
	}
}

ContextType IsContext(std::string token)
{
	std::vector<std::string> ContextStrings = {
		"main",
		"http",
		"server",
		"events",
		"location",
	};

	for (ContextType i = MAIN; i < ContextType::END; i = static_cast<ContextType>(i + 1))
	{
		if (token == ContextStrings[static_cast<int>(i)])
			return (i);
	}
	return (ContextType::END);
}

const char* ConfigParser::ConfigSyntaxError::what() const throw()
{
	return ("Error: Config file has syntax error");
}
