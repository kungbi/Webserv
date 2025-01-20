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


public:
    ServerConfig(const std::string& name, const std::string& root, int port);

    // 설정 접근자
    std::string getServerName() const;
    void setServerName(const std::string& name);

    std::string getRoot() const;
    void setRoot(const std::string& root);

    int getPort() const;
    void setPort(int port);

    // 로케이션 설정
    void addLocation(const LocationConfig& location);
    const std::vector<LocationConfig>& getLocations() const;
};

#endif // SERVERCONFIG_HPP
