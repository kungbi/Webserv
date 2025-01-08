#include "ServerContext.hpp"

ServerContext::ServerContext(IConfigContext *parent) : IConfigContext(parent)
{
}

ContextType ServerContext::getType() const
{
	return (type_);
}

void ServerContext::PrintType(std::ostream &os) const
{
}

bool ServerContext::IsValid() const
{
	return (true);
}