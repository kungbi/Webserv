#include "ConfigReader.hpp"

std::string ConfigReader::ReadFile(std::string filepath)
{
	try {
		std::ifstream config_file(filepath);
		return std::string((std::istreambuf_iterator<char>(config_file)), \
				std::istreambuf_iterator<char>());
	}
	catch (...) {
		std::cerr << "Cannot open " << filepath << std::endl;
		return ("");
	}
}