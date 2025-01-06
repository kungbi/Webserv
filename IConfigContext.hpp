#pragma once

# include <iostream>

enum ContextType
{
	MAIN,
	HTTP,
	SERVER,
};

class IConfigContext
{
	private:

	public:
		virtual ~IConfigContext();
		virtual ContextType GetType() const = 0;
		virtual void PrintType(std::ostream &os) const;
		virtual bool IsValid() const;
};