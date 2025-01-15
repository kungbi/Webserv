#include "ConfigData.hpp"

ConfigData::ConfigData(IConfigContext *root) : root_(root)
{}

ConfigData::~ConfigData()
{
	//노드 순회 삭제
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
	std::map<std::string, std::vector<std::string> > cur_dir = cur->getDirectives();

	std::cout << "Type : " << cur->getType() << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = cur_dir.begin();\
		it != cur_dir.end(); ++it)
	{
		for (std::vector<std::string>::iterator str_it = it->second.begin(); str_it != it->second.end(); ++str_it)
		{
			std::cout << "key : " << (it->first) << "   " << "value : " << *str_it << std::endl;
		}
	}
	cur = childs[0];
	cur_dir = cur->getDirectives();
	std::cout << "Type second : " << cur->getType() << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = cur_dir.begin();\
		it != cur_dir.end(); ++it)
	{
		for (std::vector<std::string>::iterator str_it = it->second.begin(); str_it != it->second.end(); ++str_it)
		{
			std::cout << "key : " << (it->first) << "   " << "value : " << *str_it << std::endl;
		}
	}
	childs = cur->getChild();
	cur = childs[0];
	cur_dir = cur->getDirectives();
	std::cout << "Type third : " << cur->getType() << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = cur_dir.begin();\
		it != cur_dir.end(); ++it)
	{
		for (std::vector<std::string>::iterator str_it = it->second.begin(); str_it != it->second.end(); ++str_it)
		{
			std::cout << "key : " << (it->first) << "   " << "value : " << *str_it << std::endl;
		}
	}
	cur = childs[1];
	cur_dir = cur->getDirectives();
	std::cout << "Type third : " << cur->getType() << std::endl;
	for (std::map<std::string, std::vector<std::string> >::iterator it = cur_dir.begin();\
		it != cur_dir.end(); ++it)
	{
		for (std::vector<std::string>::iterator str_it = it->second.begin(); str_it != it->second.end(); ++str_it)
		{
			std::cout << "key : " << (it->first) << "   " << "value : " << *str_it << std::endl;
		}
	}
	childs = cur->getChild();
	if (childs.empty())
		std::cout << "No childs" << std::endl;
	return ;
}	

void ConfigData::SearchTreetest(IConfigContext *root)
{
	IConfigContext *cur = root_;
	std::vector<IConfigContext *> childs = cur->getChild();

	while (!childs.empty())
	{
		
	}
}