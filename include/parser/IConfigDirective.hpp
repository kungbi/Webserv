#pragma once

# include "IConfigContext.hpp"

class IConfigContext;

enum DirectiveType
{
	WORKER_PROCESSES,
	WORKER_CONNECTIONS,
	ERROR_PAGE,
	LISTEN,
	SERVER_NAME,
	CLIENT_MAX_BODY_SIZE,
	ROOT,
	INDEX,
	ALLOW_METHOD,
	AUTOINDEX,
	FASTCGI_PASS,
	FASTCGI_INDEX,
	FASTCGI_PARAM,
};

class IConfigDirective
{

	private:
		int type_;
		IConfigContext *parent_;
		std::vector<std::string> values_;
		IConfigDirective();

	public:
		IConfigDirective(IConfigContext *parent, int type);
		~IConfigDirective();

		IConfigContext* getParent() const;

		void AddValue(std::string value);
		std::vector<std::string> getValues() const;

		int getType() const;
};

int IsDirective(std::string token);

