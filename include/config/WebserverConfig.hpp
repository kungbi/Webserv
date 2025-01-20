#ifndef WEBSERVERCONFIG_HPP
#define WEBSERVERCONFIG_HPP

#include <vector>
#include <string>
#include "HTTPConfig.hpp"
#include "ServerConfig.hpp"

class WebserverConfig {
private:
    HTTPConfig httpConfig; // HTTP 설정
	int workerConnections;

public:
    // 생성자
    WebserverConfig();

    // HTTP 설정 접근자
    HTTPConfig& getHTTPConfig();
    const HTTPConfig& getHTTPConfig() const;

    // 서버 설정 관리
    void addServer(const ServerConfig& server);
    const std::vector<ServerConfig>& getServers() const;
};

#endif // WEBSERVERCONFIG_HPP
