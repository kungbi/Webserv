#include "ConfigData.hpp"

ConfigData::ConfigData()
{}

ConfigData::ConfigData(IConfigContext *root)
{
	if (!root)
		throw (ConfigData::ConfigDataError());
	root_ = root;
}

ConfigData::~ConfigData()
{
	DeleteTree(root_);
}

IConfigContext* ConfigData::GetRoot()
{
	return (root_);
}

void ConfigData::PrintData(IConfigContext *parent)
{
	std::vector<IConfigContext *> childs = parent->getChild();
	for (size_t i = 0; i < childs.size(); ++i)
	{
		PrintData(childs[i]);
	}
	std::cout << "=================================\n\n"
	<< "Child Data\n"
	<< "Type : " << parent->getType() << "\n"
	<< "Options : ";
	std::vector<std::string> options = parent->getOptions();
	for (size_t i = 0; i < options.size(); ++i)
	{
		std::cout << options[i] << " ";
	}
	std::cout << std::endl;
	std::vector<IConfigDirective *> directives = parent->getDirectives();
	std::cout << "Directive count : " << directives.size() << std::endl;
	std::cout << "------------------ Directives --------------- " << std::endl;
	for (size_t i = 0; i < directives.size(); ++i)
	{
		std::cout << i+1 << " Directive\n" << "Type : " << directives[i]->getType() << std::endl;
		std::vector<std::string> tokens = directives[i]->getValues();
		std::cout << "Tokens : ";
		for (size_t j = 0; j < tokens.size(); ++j)
		{
			std::cout << tokens[j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "------------------ Directives End ----------------\n\n" << std::endl;
}

const char* ConfigData::ConfigDataError::what() const throw()
{
	return ("Error: Config Data : root is null");
}