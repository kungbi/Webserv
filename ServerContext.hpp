#pragma once

# include "IConfigContext.hpp"

enum ServerDirectives
{
	LISTEN,
	SERVER_NAME,
};

class ServerContext : public IConfigContext
{
	private:
		ContextType type_ = SERVER;

	public:
		ServerContext(IConfigContext *parent);
		ContextType getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
};