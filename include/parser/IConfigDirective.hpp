#pragma once

# include "IConfigContext.hpp"

class IConfigContext;

enum DirectiveType
{
	WORKER_PROCESSES,
	ERROR_PAGE,
	LISTEN,
	SERVER_NAME,
	ROOT,
	INDEX,
	ALLODW_METHOD,
	ACCESS_LOG,
	AUTOINDEX,
	FASTCGI_PASS,
	FASTCGI_INDEX,
	FASTCGI_PARAM,
	CLIENT_MAX_BODY_SIZE,
	RETURN,
	INCLUDE,
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

