#pragma once

# include <iostream>
# include <vector>
# include <unordered_map>

enum ContextType
{
	MAIN,
	HTTP,
	SERVER,
};

class IConfigContext
{
	protected:
		IConfigContext *parent_;
		std::vector<IConfigContext *> child_;
		std::unordered_map<std::string, std::string> directives_;

	public:
		IConfigContext(IConfigContext *parent);
		~IConfigContext();
		virtual ContextType getType() const = 0;
		virtual void PrintType(std::ostream &os) const;
		virtual bool IsValid() const;
		
		void	AddChild(IConfigContext *child);
		IConfigContext* getParent() const;
		std::vector<IConfigContext *> getChild() const;

		void	AddDirectives(std::string key, std::string value);
		std::unordered_map<std::string, std::string> getDirectives() const;
};