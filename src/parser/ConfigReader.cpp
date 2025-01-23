#include "ConfigReader.hpp"

std::string ConfigReader::ReadFile(std::string filepath)
{
    std::ifstream config_file(filepath.c_str());

    if (!config_file.is_open())
	{
        std::cerr << "Cannot open : " << filepath << std::endl;
        return ("");
    }
    std::string content((std::istreambuf_iterator<char>(config_file)),
                        std::istreambuf_iterator<char>());

    if (content.empty())
	{
        std::cerr << "File is empty : " << filepath << std::endl;
        return ("");
    }
    return (content);
}

ConfigReader::ConfigReader()
{
	default_conf_path = "./default.conf";
	// 없어도 되나?
}

std::string ConfigReader::GetDefaultPath()
{
	return (default_conf_path);
}