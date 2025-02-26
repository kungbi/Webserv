#include "ConfigReader.hpp"

std::string ConfigReader::readConfigFile(std::string filepath)
{
	// 파일스트림 생성
    std::ifstream config_file(filepath.c_str());

	// 파일 열기 실패
    if (!config_file.is_open())
    {
        std::cerr << "Cannot open : " << filepath << std::endl;
        return ("");
    }

	// 파일 내용을 읽어 content에 저장
    std::string content((std::istreambuf_iterator<char>(config_file)), std::istreambuf_iterator<char>());

	// 파일 내용이 empty
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
}

std::string ConfigReader::getDefaultPath()
{
    return (default_conf_path);
}