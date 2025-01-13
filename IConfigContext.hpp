#pragma once

# include <iostream>
# include <vector>
# include <map>
# include <stdexcept>

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
		IConfigContext *parent_;
		int	type_;
		std::vector<IConfigContext *> child_;
		std::map<std::string, std::vector<std::string> > directives_;

	public:
		IConfigContext(IConfigContext *parent, int type);
		~IConfigContext();
		int getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
		
		void	AddChild(IConfigContext *child);
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;

		void	AddDirectives(std::string key, std::string value);
		std::map<std::string, std::vector<std::string> > getDirectives() const;
};

int IsContext(std::string token);
bool IsDirective(std::string token);
