#pragma once

# include <iostream>
# include <vector>
# include <map>
# include <stdexcept>
# include "IConfigDirective.hpp"

enum ContextType
{
	MAIN,
	HTTP,
	SERVER,
	EVENTS,
	LOCATION,
	END
};

class IConfigContext
{
	private:
		IConfigContext *parent_;
		ContextType	type_;
		std::vector<IConfigContext *> child_;
		std::vector<IConfigDirective *> directives_;

		void	AddChild(IConfigContext *child);
	public:
		IConfigContext(IConfigContext *parent, ContextType type);
		~IConfigContext();
		ContextType getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
		
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;

		void	AddDirectives(IConfigDirective *directive);
		std::vector<IConfigDirective *> getDirectives() const;

};

ContextType IsContext(std::string token);
void DeleteTree(IConfigContext *root);