#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>

class LocationConfig {
private:
    std::string uri;          // 경로 (예: /images, /api)
    std::string root;         // 루트 디렉토리
    bool autoIndex;           // 디렉토리 인덱싱 허용 여부
    std::string redirect;     // 리다이렉트 경로

public:
    LocationConfig(const std::string& uri = "/", const std::string& root = "/var/www/html", bool autoIndex = false, const std::string& redirect = "");

    // 설정 접근자
    std::string getURI() const;
    void setURI(const std::string& uri);

    std::string getRoot() const;
    void setRoot(const std::string& root);

    bool isAutoIndex() const;
    void setAutoIndex(bool value);

    std::string getRedirect() const;
    void setRedirect(const std::string& redirect);
};

#endif // LOCATIONCONFIG_HPP
