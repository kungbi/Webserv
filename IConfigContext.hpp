#pragma once

# include <iostream>
# include <vector>
# include <map>
# include <stdexcept>
# include "IConfigDirective.hpp"


class IConfigContext
{
	private:
		IConfigContext *parent_;
		int	type_;
		std::vector<IConfigContext *> child_;
		std::vector<IConfigDirective *> directives_;

		void	AddChild(IConfigContext *child);
	public:
		IConfigContext(IConfigContext *parent, int type);
		~IConfigContext();
		int getType() const;
		void PrintType(std::ostream &os) const;
		bool IsValid() const;
		
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;

		void	AddDirectives(IConfigDirective *directive);
		std::vector<IConfigDirective *> getDirectives() const;

		enum ContextType
		{
			MAIN,
			HTTP,
			SERVER,
			EVENTS,
			LOCATION,
		};
};

int IsContext(std::string token);
void DeleteTree(IConfigContext *root);