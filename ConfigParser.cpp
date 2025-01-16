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
		//delete tree(root)
		return (NULL);
	}
	return (root);
}

void ConfigParser::DeleteTree(IConfigContext *root)
{
	IConfigContext *cur = root;
	std::vector<IConfigContext *> childs = root->getChild();

	if (!root)
		return ;
	if (childs.empty())
		return ;
	for (size_t i = 0; i < childs.size(); ++i)
	{
		DeleteTree(childs[i]);
	}
	delete (root);
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
		int ContextType = IsContext(*it);
		if (ContextType > 0)
		{
			if (*(++it) != "{") {
				throw (ConfigParser::ConfigSyntaxError());
			}

			if (it == last_it) {
				throw (ConfigParser::ConfigSyntaxError());
			}

			int BracketCount = 1;
			std::vector<std::string> SubTokens;
			IConfigContext* node = new IConfigContext(parent, ContextType);
			
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
		else if (IsDirective(*it))
		{
			//*it = 지시어 토큰
			if (it == last_it)
				throw (ConfigParser::ConfigSyntaxError());

			std::string Directive = *it;
			++it;

			while (it != tokens.end() && *it != ";")
			{
				std::string::iterator TokenIterEnd = it->end();

				--TokenIterEnd;
				if (*TokenIterEnd == ';') {
					parent->AddDirectives(Directive, it->substr(0, it->size() - 1));
					break ;
				}
				parent->AddDirectives(Directive, *it);
				++it;
			}
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
