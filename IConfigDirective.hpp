#pragma once

# include "IConfigContext.hpp"


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
		int getType() const;

		IConfigContext* getParent() const;

		void AddValue(std::string value);
		std::vector<std::string> getValues() const;

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
	};
};

int IsDirective(std::string token);