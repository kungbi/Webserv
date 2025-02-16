#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <string>
#include <vector>
#include <map>
#include <string>
#include "LocationConfig.hpp"

class ServerConfig {
private:
	int port;                 // 포트 번호
	std::string serverName;   // 서버 이름
	std::string root;         // 루트 디렉토리
	std::vector<std::string> index;
	int client_max_body_size;

	std::map<std::string, std::string> errorPages;


	std::map<std::string, LocationConfig> exactLocations; // = 로케이션 설정
	std::map<std::string, LocationConfig> prefixLocations; // ~, ~*, etc 로케이션 설정
	std::map<std::string, LocationConfig> regexLocations; // 로케이션 설정

	ServerConfig(void);

public:
	ServerConfig(
		const std::string& serverName, 
		const std::string& root, 
		int port, 
		const std::vector<std::string>& index, 
		int client_max_body_size, 
		const std::map<std::string, std::string>& errorPages,
		const std::map<std::string, LocationConfig>& exactLocations,
		const std::map<std::string, LocationConfig>& prefixLocations,
		const std::map<std::string, LocationConfig>& regexLocations
	);

	std::string getServerName() const;
	std::string getRoot() const;
	int getPort() const;
	std::vector<std::string> getIndex() const;
	int getClientMaxBodySize() const;
	std::map<std::string, std::string> getErrorPages() const;
	std::map<std::string, LocationConfig> getExactLocations() const;
	std::map<std::string, LocationConfig> getPrefixLocations() const;
	std::map<std::string, LocationConfig> getRegexLocations() const;
};

#endif
