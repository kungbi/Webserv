#include "IConfigDirective.hpp"

IConfigDirective::IConfigDirective()
{}

IConfigDirective::IConfigDirective(IConfigContext *parent, int type) : type_(type), parent_(parnet)
{
}

IConfigDirective::~IConfigDirective()
{}

IConfigContext* IConfigDirective::getParent() const
{
	return (parent_);
}

void IConfigDirective::AddValue(std::string value)
{
	values_.push_back(value);
}

int IConfigDirective::getType() const
{
	return (type_);
}

std::vector<std::string> IConfigDirective::getValues() const
{
	return (values_);
}

int IsDirective(std::string token)
{
	std::vector<std::string> DirectiveStrings;
	DirectiveStrings.push_back("worker_processes");
	DirectiveStrings.push_back("error_page");
	DirectiveStrings.push_back("listen");
	DirectiveStrings.push_back("server_name");
	DirectiveStrings.push_back("root");
	DirectiveStrings.push_back("index");
	DirectiveStrings.push_back("allow_method");
	DirectiveStrings.push_back("access_log");
	DirectiveStrings.push_back("autoindex");

	for (size_t i = 0; i < DirectiveStrings.size(); ++i)
	{
		if (token == DirectiveStrings[i])
			return (i);
	}
	return (-1);
}