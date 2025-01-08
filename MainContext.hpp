#pragma once

# include "IConfigContext.hpp"

enum MainDirectives
{
	WORKER_PROCESSES,
};

class MainContext : public IConfigContext
{
	private:
		ContextType type_ = MAIN;

	public:
		MainContext(unsigned int worker_processes);
		ContextType GetType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
};
