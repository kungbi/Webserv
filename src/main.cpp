#include "Webserver.hpp"
#include "WebserverConfig.hpp"


void initializeConfig(WebserverConfig& config) {
	 // Webserver 설정
    WebserverConfig webConfig;

    // HTTP 설정
    HTTPConfig& httpConfig = webConfig.getHTTPConfig();
    httpConfig.setServerHeader("MyCustomWebserver");
    httpConfig.setKeepAlive(true);
    httpConfig.setMaxRequestSize(10240);

    // 서버 1 설정
    ServerConfig server1("localhost", "/var/www/html", 8080);

    // 서버 1의 로케이션 설정
    LocationConfig loc1("/images", "/var/www/html/images", true, "");
    LocationConfig loc2("/api", "/var/www/html/api", false, "https://api.example.com");

    server1.addLocation(loc1);
    server1.addLocation(loc2);

    // 서버 2 설정
    ServerConfig server2("example.com", "/var/www/example", 9090);

    // 서버 2의 로케이션 설정
    LocationConfig loc3("/", "/var/www/example", true, "");

    server2.addLocation(loc3);

    // WebserverConfig에 서버 추가
    webConfig.addServer(server1);
    webConfig.addServer(server2);

    // 설정 출력
    std::cout << "HTTP Server Header: " << httpConfig.getServerHeader() << std::endl;
    std::cout << "Keep-Alive: " << (httpConfig.isKeepAlive() ? "Enabled" : "Disabled") << std::endl;
    std::cout << "Max Request Size: " << httpConfig.getMaxRequestSize() << " bytes" << std::endl;

    const std::vector<ServerConfig>& servers = webConfig.getServers();
    for (size_t i = 0; i < servers.size(); ++i) {
        const ServerConfig& server = servers[i];
        std::cout << "Server " << i + 1 << ": " << server.getServerName() << " on port " << server.getPort() << std::endl;
        const std::vector<LocationConfig>& locations = server.getLocations();
        for (size_t j = 0; j < locations.size(); ++j) {
            const LocationConfig& loc = locations[j];
            std::cout << "  Location " << j + 1 << ": " << loc.getURI() << " -> " << loc.getRoot() << std::endl;
        }
    }

}

int main(int argc, char* argv[]) {


	Webserver webserver("config.conf");
	webserver.start();

	return 0;
}