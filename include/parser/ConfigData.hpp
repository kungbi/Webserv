#pragma once

# include "IConfigContext.hpp"
# include "IConfigDirective.hpp"

class ConfigData
{
	private:
		IConfigContext *root_;
		ConfigData();

	public:
		ConfigData(IConfigContext *root);
		~ConfigData(); // 트리 전부 삭제.
		IConfigContext *GetRoot();
		void PrintData(IConfigContext *parent);

	class ConfigDataError : public std::exception
	{
		public:
			virtual const char* what() const throw();
	};
};