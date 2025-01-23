#pragma once

# include "IConfigContext.hpp"

enum DirectiveType
{
	WORKER_PROCESSES,
	ERROR_PAGE,
	LISTEN,
	SERVER_NAME,
	CLIENT_MAX_BODY_SIZE,
	ROOT,
	INDEX,
	ALLODW_METHOD,
	AUTOINDEX,
	END
};

class IConfigDirective
{

	private:
		DirectiveType type_;
		IConfigContext *parent_;
		std::vector<std::string> values_;
		IConfigDirective();

	public:
		IConfigDirective(IConfigContext *parent, DirectiveType type);
		~IConfigDirective();

		IConfigContext* getParent() const;

		void AddValue(std::string value);
		std::vector<std::string> getValues() const;

		DirectiveType getType() const;
};

DirectiveType IsDirective(std::string token);

