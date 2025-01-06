#include "IConfigContext.hpp"

IConfigContext::~IConfigContext()
{}

void IConfigContext::PrintType(std::ostream &os) const
{
	os << "Context Type: " << GetType() << std::endl;
}

bool IConfigContext::IsValid() const
{
	return (true);
}

