#include "ConfigData.hpp"

ConfigData::ConfigData(IConfigContext *root)
{
	// try {
	// 	ValidCheck(root);
	// } catch (std::exception &e) {
	// 	std::cerr << e.what() << std::endl;
	// 	DeleteTree(root);
	// 	throw ;
	// }
	root_ = root;
}

void ConfigData::ValidCheck(IConfigContext *root)
{
	if (!root)
		return ;

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
	int parent = dir->getParent()->getType();

	if (parent != MAIN)
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
	int parent = dir->getParent()->getType();

	if (parent != HTTP && parent != SERVER && parent != LOCATION)
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
	int parent = dir->getParent()->getType();

	if (parent != SERVER)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();

	if (tokens.empty())
	{
		tokens.push_back("80");
		return ;
	}
	if (tokens.size() != 1)
		throw ;
	// 유효성 검증 어디까지?
}

void ConfigData::ServerNameDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();

	if (parent != SERVER)
		throw ;
	
	std::vector<std::string> tokens = dir->getValues();
	if (tokens.empty())
	{
		tokens.push_back("");
	}
}

void ConfigData::ClientMaxBodySizeDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();

	if (parent != HTTP && parent != SERVER && parent != LOCATION)
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
	std::string::iterator end = (*token_it).end();
	end--;
	if ((!isdigit(*end)) && *end != 'm')
		throw ;
	for (std::string::iterator it = (*token_it).begin(); it < end; ++it)
	{
		if (!isdigit(*it))
			throw ;
	}
}

void ConfigData::RootDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();

	if (parent != HTTP && parent != SERVER && parent != LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();

	if (tokens.size() != 1)
		throw ;
}

void ConfigData::AllowMethodDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();

	if (parent != MAIN) // Allodwmethod   어디에 속할까?
		throw ;

	std::vector<std::string> tokens = dir->getValues();
	
	if (tokens.empty())
		throw ;

	std::vector<std::string> methods;
	methods.push_back("connect");
	methods.push_back("delete");
	methods.push_back("get");
	methods.push_back("head");
	methods.push_back("options");
	methods.push_back("patch");
	methods.push_back("post");
	methods.push_back("put");

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		for (size_t j = 0; j < methods.size(); ++j)
		{
			if (tokens[i] == methods[j])
				break ;
		}
		if (i == tokens.size())
			throw ;
	}
}

void ConfigData::IndexDirectiveCheck(IConfigDirective *dir)
{
	int16_t parent = dir->getParent()->getType();

	if (parent != HTTP && parent != SERVER && parent != LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();
	if (tokens.empty())
	{
		tokens.push_back("index.html");
		return ;
	}
	for (size_t i = 0; i < tokens.size(); ++i)
	{
		std::string token = tokens[i];
		for (size_t j = 0; j < token.size(); ++j)
		{
			if (token[j] == '/')
				throw ;
		}
	}
}

void ConfigData::AutoIndexDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();
	if (parent != HTTP && parent != SERVER  && parent != LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();
	if (tokens.empty())
	{
		tokens.push_back("off");
		return ;
	}
	if (tokens.size() != 1)
		throw ;
	if (tokens[0] != "on" && tokens[0] != "off")
		throw ;
}

void ConfigData::ReturnDirectiveCheck(IConfigDirective *dir)
{
	int parent = dir->getParent()->getType();
	if (parent != SERVER && parent != LOCATION)
		throw ;

	std::vector<std::string> tokens = dir->getValues();
	if (tokens.empty())
		throw ;
	if (tokens.size() > 2)
		throw ;
	for (size_t i = 0; i < tokens.size(); ++i)
	{
		if (!IsStatusNumber(tokens[i]))
			throw ;
	}
}

ConfigData::DirectiveCheckFunction ConfigData::getDirectiveCheckFuntion(int type)
{
	if (type == WORKER_PROCESSES)
		return &ConfigData::WorkerProcessesDirectiveCheck;
	if (type == ALLODW_METHOD)
		return &ConfigData::AllowMethodDirectiveCheck;
	if (type == ERROR_PAGE)
		return &ConfigData::ErrorPageDirectiveCheck;
	if (type == LISTEN)
		return &ConfigData::ListenDirectiveCheck;
	if (type == SERVER_NAME)
		return &ConfigData::ServerNameDirectiveCheck;
	if (type == CLIENT_MAX_BODY_SIZE)
		return &ConfigData::ClientMaxBodySizeDirectiveCheck;
	if (type == ROOT)
		return &ConfigData::RootDirectiveCheck;
	if (type == INDEX)
		return &ConfigData::IndexDirectiveCheck;
	if (type == AUTOINDEX)
		return &ConfigData::AutoIndexDirectiveCheck;
	return NULL;
}

bool ConfigData::CallDirectiveCheck(std::vector<IConfigDirective *> directives)
{
	for (size_t i = 0; i < directives.size(); ++i)
	{
		int type = directives[i]->getType();
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
	if (node->getParent() != NULL)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::HttpContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != MAIN)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();

	//에러페이지 하나도 없으면 throw?

	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::ServerContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != HTTP)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();

	//listen 없을 시 기본 포트 80
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::EventsContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != MAIN)
		throw ;

	std::vector<IConfigDirective *> directives = node->getDirectives();
	if (!CallDirectiveCheck(directives))
		throw ;
}

void ConfigData::LocationContextCheck(IConfigContext *node)
{
	if (node->getParent()->getType() != SERVER)
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
	std::cout << "Type third : " << cur->getType() << std::endl;
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