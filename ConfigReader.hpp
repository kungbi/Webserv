#pragma once

# include <fstream>
# include <iostream>

class ConfigReader
{
	private:
		// 기본경로 설정하기?
	public:
		std::string ReadFile(std::string filepath);
};