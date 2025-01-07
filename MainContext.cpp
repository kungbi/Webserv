#include "MainContext.hpp"

MainContext::MainContext(unsigned int worker_processes) : worker_processes_(worker_processes)
{}

ContextType MainContext::GetType() const
{
	return (type_);
}

void MainContext::PrintType(std::ostream &os) const
{
	os << "Context Type: " << GetType() << std::endl;
}

bool MainContext::IsValid() const
{
	if (worker_processes_ < 0)
		throw ; // exception
}