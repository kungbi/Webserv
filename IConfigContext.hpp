#pragma once

# include <iostream>
# include <vector>
# include <map>

enum ContextType
{
	MAIN,
	HTTP,
	SERVER,
	EVENTS,
	LOCATION,
	CONTEXT_END
};

enum MainDirectives
{
	WORKER_PROCESSES,
	ERROR_LOG,
	PID,
	USER,
};

enum HttpDirectives
{};

enum ServerDirectives
{};

enum EventsDirectives
{};

enum LocationDirectives
{};

class IConfigContext
{
	private:
		int	type_;
		IConfigContext *parent_;
		std::vector<IConfigContext *> child_;
		std::map<std::string, std::vector<std::string> > directives_;

	public:
		IConfigContext(IConfigContext *parent, int type);
		~IConfigContext();
		ContextType getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
		
		void	AddChild(IConfigContext *child);
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;

		void	AddDirectives(std::string key, std::string value);
		std::map<std::string, std::vector<std::string> > getDirectives() const;
};

bool IsContext(std::string token);