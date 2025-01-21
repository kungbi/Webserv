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
	WebserverConfig(const HTTPConfig& httpConfig, int workerConnections);

	HTTPConfig& getHTTPConfig() const;
	int getWorkerConnections() const;
};

#endif // WEBSERVERCONFIG_HPP
