#include "IConfigContext.hpp"

IConfigContext::IConfigContext(IConfigContext *parent, int type) : parent_(parent), type_(type)
{
	if (parent)
	{
		parent->AddChild(this);
	}
}

IConfigContext::~IConfigContext()
{}

void IConfigContext::AddChild(IConfigContext *child)
{
	child_.push_back(child);
}

void	IConfigContext::AddDirectives(IConfigDirective *directive)
{
	directives_.push_back(directive);
}

IConfigContext* IConfigContext::getParent() const
{
	return (parent_);
}

std::vector<IConfigContext *> IConfigContext::getChild() const
{
	return (child_);
}

std::vector<IConfigDirective*> IConfigContext::getDirectives() const
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

int IConfigContext::getType() const
{
	return (type_);
}

void DeleteTree(IConfigContext *root)
{
	std::vector<IConfigContext *> childs = root->getChild();

	if (!root)
		return ;
	for (size_t i = 0; i < childs.size(); ++i)
	{
		DeleteTree(childs[i]);
	}
	delete (root);
	std::vector<IConfigDirective *> directives = root->getDirectives();
	for (size_t i = 0; i < directives.size(); ++i)
	{
		delete directives[i];
	}
}

std::vector<std::string> IConfigContext::getOptions() const
{
	return (options_);
}