#pragma once

# include <iostream>
# include <vector>
# include <map>
# include <stdexcept>
# include "IConfigDirective.hpp"

class IConfigDirective;

enum ContextType
{
	MAIN,
	HTTP,
	SERVER,
	EVENTS,
	LOCATION,
};

class IConfigContext
{
	private:
		IConfigContext *parent_;
		int	type_;
		std::vector<IConfigContext *> child_;
		std::vector<IConfigDirective *> directives_;
		std::vector<std::string> options_;

		void	AddChild(IConfigContext *child);
	public:
		IConfigContext(IConfigContext *parent, int type);
		~IConfigContext();
		int getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
		
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;
		std::vector<std::string> getOptions() const;

		void	AddDirectives(IConfigDirective *directive);
		void	AddOptions(std::string token);
		std::vector<IConfigDirective *> getDirectives() const;

};

int IsContext(std::string token);
void DeleteTree(IConfigContext *root);