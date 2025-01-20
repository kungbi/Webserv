#include "ConfigData.hpp"

ConfigData::ConfigData(IConfigContext *root)
{
	try {
		ValidCheck(root);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		DeleteTree(root);
		throw (something);
	}
}

void ConfigData::ValidCheck(IConfigContext *root)
{
	if (!root)
		return ;

	IConfigContext *cur = root;
	std::vector<IConfigContext *> childs = root->getChild();
	
	void (ConfigData::*ValidFunctions[])(IConfigContext *node) = {
		&ConfigData::MainContextCheck, 
		&ConfigData::HttpContextCheck, 
		&ConfigData::ServerContextCheck,
		&ConfigData::EventsContextCheck,
		&ConfigData::LocationContextCheck
	};

	for (size_t i = 0; i < childs.size(); ++i)
	{
		try {
			ValidCheck(childs[i]);
		}
		catch (...) {
			throw ;
		}
	}

	int node_type = root->getType();
	try {
		(this->*ValidFunctions[node_type])(root);
	} catch (...) {
		throw ;
	}
}

void ConfigData::MainContextCheck(IConfigContext *node)
{
	std::map<std::string, std::vector<std::string> > directives = node->getDirectives();
	
	if (directives.count("worker_processes") == 0) {
		node->AddDirectives("worker_processes", "1");
		return ;
	}
	if (directives["worker_processes"].size() > 1)
		throw ;
	int worker_processes = std::atoi(directives["worker_processes"][0].c_str());
	if (worker_processes < 1 || worker_processes > 10)
		throw ;
}

void ConfigData::HttpContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != MAIN)
		throw ;

	std::map<std::string, std::vector<std::string> > directives = node->getDirectives();

	if (directives.count("error_page") < 2)
		throw ;
	
}

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