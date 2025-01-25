#pragma once

# include "IConfigContext.hpp"
# include "HTTPConfig.cpp"
# include "ServerConfig.hpp"
# include "WebserverConfig.hpp"

class IConfigContext;
class IConfigDirective;

class Adapter
{
	private:
		Adapter();
		~Adapter();
		bool CheckContextDependency(IConfigContext *node);
		bool CheckDirectiveDependency(IConfigDirective *dir);
	
	public:
		WebserverConfig* Adapt(IConfigContext *root);
}