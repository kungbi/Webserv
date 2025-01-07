#pragma once

# include "IConfigContext.hpp"

class HttpContext : public IConfigContext
{
	private:
		ContextType type_ = HTTP;

	public:
		HttpContext();
		ContextType GetType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
}