#include "ConfigData.hpp"

ConfigData::ConfigData(IConfigContext *root)
{
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

void ConfigData::SearchTree()
{
	IConfigContext *cur;

	cur = GetRoot();

	std::vector<IConfigContext *> childs = cur->getChild();
	std::vector<IConfigDirective *> directives = cur->getDirectives();

	std::cout << "Type : " << cur->getType() << std::endl;
	for (std::vector<IConfigDirective *>::iterator it = directives.begin(); it < directives.end(); ++it)
	{
		std::cout << "Directive Type : " << (*it)->getType() << std::endl;
		std::cout << "Directive Contents : " << std::endl;
		std::vector<std::string> tokens = (*it)->getValues();
		for (std::vector<std::string>::iterator token = tokens.begin(); token < tokens.end(); ++token)
		{
			std::cout << *token << " ";
		}
	}
	cur = childs[0];
	directives = cur->getDirectives();
	std::cout << "Type second : " << cur->getType() << std::endl;
	for (std::vector<IConfigDirective *>::iterator it = directives.begin(); it < directives.end(); ++it)
	{
		std::cout << "Directive Type : " << (*it)->getType() << std::endl;
		std::cout << "Directive Contents : " << std::endl;
		std::vector<std::string> tokens = (*it)->getValues();
		for (std::vector<std::string>::iterator token = tokens.begin(); token < tokens.end(); ++token)
		{
			std::cout << *token << " ";
		}
	}
	childs = cur->getChild();
	cur = childs[0];
	directives = cur->getDirectives();
	for (std::vector<IConfigDirective *>::iterator it = directives.begin(); it < directives.end(); ++it)
	{
		std::cout << "Directive Type : " << (*it)->getType() << std::endl;
		std::cout << "Directive Contents : " << std::endl;
		std::vector<std::string> tokens = (*it)->getValues();
		for (std::vector<std::string>::iterator token = tokens.begin(); token < tokens.end(); ++token)
		{
			std::cout << *token << " ";
		}
	}
	cur = childs[1];
	directives = cur->getDirectives();
	std::cout << "Type third : " << cur->getType() << std::endl;
	std::cout << "Type third : Location" << cur->getType() << std::endl;
	std::vector<std::string> options = cur->getOptions();
	std::cout << "options : ";
	for (std::vector<std::string>::iterator it = options.begin(); it < options.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout<<std::endl;
	for (std::vector<IConfigDirective *>::iterator it = directives.begin(); it < directives.end(); ++it)
	{
		std::cout << "Directive Type : " << (*it)->getType() << std::endl;
		std::cout << "Directive Contents : " << std::endl;
		std::vector<std::string> tokens = (*it)->getValues();
		for (std::vector<std::string>::iterator token = tokens.begin(); token < tokens.end(); ++token)
		{
			std::cout << *token << " ";
		}
	}
	childs = cur->getChild();
	if (childs.empty())
		std::cout << "No childs" << std::endl;
	return ;
}	

// void ConfigData::SearchTreetest(IConfigContext *root)
// {
// 	IConfigContext *cur = root_;
// 	std::vector<IConfigContext *> childs = cur->getChild();

// 	while (!childs.empty())
// 	{
		
// 	}
// }