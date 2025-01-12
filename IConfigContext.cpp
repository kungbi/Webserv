#include "IConfigContext.hpp"

IConfigContext::IConfigContext(IConfigContext *parent, int type) : parent_(parent), type_(type)
{
	if (parent)
	{
		parent->AddChild(this);
	}
}

IConfigContext::~IConfigContext()
{
	for (std::vector<IConfigContext *>::iterator it = child_.begin(); it != child_.end();)
		delete *it;
}

void IConfigContext::AddChild(IConfigContext *child)
{
	child_.push_back(child);
}

IConfigContext* IConfigContext::getParent() const
{
	return (parent_);
}

std::vector<IConfigContext *> IConfigContext::getChild() const
{
	return (child_);
}

void IConfigContext::AddDirectives(std::string key, std::string value)
{
	directives_[key].push_back(value);
}

std::map<std::string, std::vector<std::string> > IConfigContext::getDirectives() const
{
	return (directives_);
}

void IConfigContext::PrintType(std::ostream &os) const
{
	os << "Context Type: " << getType() << std::endl;
}

bool IConfigContext::IsValid() const
{
	return (true);
}

