#include "HttpContext.hpp"

HttpContext::HttpContext(IConfigContext *parent) : IConfigContext(parent)
{
}

ContextType HttpContext::getType() const
{
	return (type_);
}

bool HttpContext::IsValid() const
{
	return (true);
}

void HttpContext::PrintType(std::ostream &os) const
{
	os << "Context Type: " << getType() << std::endl;
}