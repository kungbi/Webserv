#ifndef HTTPCONFIG_HPP
#define HTTPCONFIG_HPP

#include <string>

class HTTPConfig {
private:
    std::string serverHeader; // 기본 Server 헤더
    bool keepAlive;           // Keep-Alive 설정
    size_t maxRequestSize;    // 최대 요청 크기

public:
    HTTPConfig(const std::string& serverHeader = "MyWebserver", bool keepAlive = true, size_t maxRequestSize = 8192);

    // 설정 접근자
    std::string getServerHeader() const;
    void setServerHeader(const std::string& header);

    bool isKeepAlive() const;
    void setKeepAlive(bool value);

    size_t getMaxRequestSize() const;
    void setMaxRequestSize(size_t size);
};

#endif // HTTPCONFIG_HPP
