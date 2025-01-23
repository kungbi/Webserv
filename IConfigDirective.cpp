#include "IConfigDirective.hpp"

IConfigDirective::IConfigDirective()
{}

IConfigDirective::IConfigDirective(IConfigContext *parent, DirectiveType type) : type_(type), parent_(parent)
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

DirectiveType IConfigDirective::getType() const
{
	return (type_);
}

std::vector<std::string> IConfigDirective::getValues() const
{
	return (values_);
}

DirectiveType IsDirective(std::string token)
{
	std::vector<std::string> DirectiveStrings = {
		"worker_processes",
		"error_page",
		"listen",
		"server_name",
		"root",
		"index",
		"allow_method",
		"access_log",
		"autoindex"
    };

	for (DirectiveType i = WORKER_PROCESSES; i <= DirectiveType::END; i = static_cast<DirectiveType>(i + 1))
	{
		if (token == DirectiveStrings[static_cast<int>(i)])
			return (i);
	}
	return (END);
}