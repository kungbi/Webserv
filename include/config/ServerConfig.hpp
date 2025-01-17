#ifndef SERVERCONFIG_HPP
#define SERVERCONFIG_HPP

#include <string>
#include <vector>
#include "LocationConfig.hpp"

class ServerConfig {
private:
    std::string serverName;   // 서버 이름
    std::string root;         // 루트 디렉토리
    int port;                 // 포트 번호
    std::vector<LocationConfig> locations; // 로케이션 설정

public:
    ServerConfig(const std::string& name = "localhost", const std::string& root = "/var/www", int port = 80);

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
