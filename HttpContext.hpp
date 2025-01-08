#pragma once

# include "IConfigContext.hpp"

enum HttpDirectives
{
};

class HttpContext : public IConfigContext
{
	private:
		ContextType type_ = HTTP;

	public:
		HttpContext(IConfigContext *parent);
		ContextType getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
};