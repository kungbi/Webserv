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

	int node_type = root->getType(); //문제 생길수도 있으니 주의
	try {
		(this->*ValidFunctions[node_type])(root);
	} catch (...) {
		throw ;
	}
}

void ConfigData::WorkerProcessesDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::MAIN)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();

	if (tokens.empty())
		tokens.push_back("1");
	if (tokens.size() > 1)
		throw ;
	int worker_process = std::atoi(tokens[1].c_str());
	if (worker_process < 1 || worker_process > 10)
		throw ;
}

void ConfigData::ErrorPageDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::HTTP || parent != ContextType::SERVER || parent != ContextType::LOCATION)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();

	if (tokens.size() < 2)
		throw ;
	std::vector<std::string>::iterator end_token = tokens.end();
	--end_token;
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		if (!IsStatusNumber(*it))
			throw ;
	}
	if (end_token[0] != "/")
		throw ;
}

void ConfigData::ListenDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::SERVER)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();
	if (tokens.size() != 1)
		throw ;
	// 유효성 검증 어디까지?
}

void ConfigData::ServerNameDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::SERVER)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();
	if (tokens.empty())
	{
		tokens.push_back("");
	}
}

void ConfigData::ClientMaxBodySizeDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::HTTP || parent != ContextType::SERVER || parent != ContextType::LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();

	if (tokens.empty())
	{
		tokens.push_back("1024");
	}
	if (tokens.size() != 1)
		throw ;
	std::vector<std::string>::iterator token_it = tokens.end();
	token_it--;
	std::string::iterator it = (*token_it).begin();
	std::string::iterator end = (*token_it).end();
	end--;
	if ((!isdigit(*end)) && *end != 'm')
		throw ;
	for (it; it < end; ++it)
	{
		if (!isdigit(*it))
			throw ;
	}
}

void ConfigData::RootDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != ContextType::HTTP || parent != ContextType::SERVER || parent != ContextType::LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();

	if (tokens.size() != 1)
		throw ;
}

void ConfigData::AllowMethodDirectiveCheck(IConfigDirective *dir)
{
	ContextType parent = dir->getParent()->getType();

	if (parent != )
}

ConfigData::DirectiveCheckFunction ConfigData::getDirectiveCheckFuntion(DirectiveType type)
{
	if (type == DirectiveType::WORKER_PROCESSES)
		return ConfigData::WorkerProcessesDirectiveCheck;
	if (type == DirectiveType::ALLODW_METHOD)
		return ConfigData::AllowMethodDirectiveCheck;
	if (type == DirectiveType::ERROR_PAGE)
		return ConfigData::ErrorPageDirectiveCheck;
	if (type == DirectiveType::LISTEN)
		return ConfigData::ListenDirectiveCheck;
	if (type == DirectiveType::SERVER_NAME)
		return ConfigData::ServerNameDirectiveCheck;
	if (type == DirectiveType::CLIENT_MAX_BODY_SIZE)
		return ConfigData::ClientMaxBodySizeDirectiveCheck;
	if (type == DirectiveType::ROOT)
		return ConfigData::RootDirectiveCheck;
	if (type == DirectiveType::INDEX)
		return ConfigData::IndexDirectiveCheck;
	if (type == DirectiveType::AUTOINDEX)
		return ConfigData::AutoIndexDirectiveCheck;
}

bool ConfigData::CallDirectiveCheck(std::vector<IConfigDirective *> directives)
{
	for (size_t i = 0; i < directives.size(); ++i)
	{
		DirectiveType type = directives[i]->getType();
		ConfigData::DirectiveCheckFunction CheckFunction = getDirectiveCheckFuntion(type);
		try {
			(this->*CheckFunction)(directives[i]);
		}
		catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			return (false);
		}
	}
	return (true);
}

void ConfigData::MainContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != NULL)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::HttpContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != ContextType::MAIN)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();

	//에러페이지 하나도 없으면 throw?

	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::ServerContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != ContextType::HTTP)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();

	//listen 없을 시 기본 포트 80
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::EventsContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != ContextType::MAIN)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::LocationContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != ContextType::SERVER)
		throw ;
	
	std::vector<IConfigDirective *> directives = node->getDirectives();
	if (!CallDirectiveCheck(directives))
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