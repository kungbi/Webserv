#pragma once

#include "IConfigContext.hpp"
#include "IConfigDirective.hpp"

class ConfigData
{
	private:
		IConfigContext *dataRoot_;
		ConfigData();
	
	public:
		ConfigData(IConfigContext* contextRoot);
		~ConfigData();
		
		IConfigContext *getRoot();
		void printConfigData(IConfigContext *parent);

	class ConfigSyntaxError : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
};
