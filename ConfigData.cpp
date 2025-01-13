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

	std::cout << "Type : " << cur->getType() << std::endl;
	cur = childs[0];
	std::cout << "Type 2 : " << cur->getType() << std::endl;
	
	if (childs.empty())
		return ;
}	