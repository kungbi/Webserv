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
