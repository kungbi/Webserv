#pragma once

# include "IConfigContext.hpp"
# include "ServerConfig.hpp"
# include "HTTPConfig.hpp"
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
		WebserverConfig AdapterRucrusive(IConfigContext *root);
	
	public:
		WebserverConfig* Adapt(IConfigContext *root);
};
