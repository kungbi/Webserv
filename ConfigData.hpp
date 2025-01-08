#pragma once

# include "IConfigContext.hpp"

class ConfigData
{
	private:
		IConfigContext *root_;

	public:
		ConfigData(IConfigContext *root);
		~ConfigData(); // 트리 전부 삭제.
};