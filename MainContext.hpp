#pragma once

# include <iostream>
# include "IConfigContext.hpp"

class MainContext : public IConfigContext
{
	private:
		ContextType type = MAIN;
		

	public:
		ContextType GetType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;

};
