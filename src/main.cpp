#include "Webserver.hpp"
#include "WebserverConfig.hpp"
#include "ServerConfig.hpp"
#include "HTTPConfig.hpp"
#include "LocationConfig.hpp"

WebserverConfig* initializeConfig() {
	// LocationConfig를 위한 벡터 생성 및 초기화
	std::vector<std::string> location1Methods;
	location1Methods.push_back("GET");
	location1Methods.push_back("POST");

	std::vector<std::string> location1FastcgiIndex;
	location1FastcgiIndex.push_back("index.php");
	location1FastcgiIndex.push_back("main.php");

	LocationConfig location1(
		"/var/www/images", false, "/redirect/path", location1Methods, "/usr/local/bin/php-cgi", location1FastcgiIndex
	);

	std::vector<std::string> location2Methods;
	location2Methods.push_back("GET");

	std::vector<std::string> location2FastcgiIndex;
	location2FastcgiIndex.push_back("api.py");

	LocationConfig location2(
		"/var/www/api", false, "", location2Methods, "/usr/bin/python-cgi", location2FastcgiIndex
	);

	// 빈 map 생성
	std::map<std::string, LocationConfig> emptyLocations;
	std::map<std::string, std::string> errorPages;
	errorPages["404"] = "/error_pages/404.html";
	errorPages["500"] = "/error_pages/500.html";

	std::vector<std::string> server1Index;
	server1Index.push_back("index.html");
	server1Index.push_back("index.htm");

	ServerConfig serverConfig1(
		"MyServer1", "/var/www/html", 8080, server1Index, 1024 * 1024,
		errorPages, emptyLocations, emptyLocations, emptyLocations
	);

	// HTTPConfig 인스턴스 생성
	std::vector<ServerConfig> servers;
	servers.push_back(serverConfig1);

	HTTPConfig httpConfig(servers);

	// WebserverConfig 인스턴스 생성
	return new WebserverConfig(httpConfig, 1024);
}

#include <stdlib.h>

void leak() {
	system("leaks webserv");
}

Webserver* dependencyInjection(WebserverConfig* config) {
	Kqueue* kqueue = new Kqueue(config->getWorkerConnections());
	Servers* servers = new Servers(*kqueue);
	for (std::vector<ServerConfig>::const_iterator it = config->getHTTPConfig().getServers().begin(); it != config->getHTTPConfig().getServers().end(); ++it) {
		ServerConfig serverConfig = *it;
		Socket* serverSocket = new Socket("127.0.0.1", serverConfig.getPort());
		Server* server = servers->createServer(*serverSocket, serverConfig, *kqueue);

		kqueue->addEvent(server->getSocketFd(), SERVER, server->getSocketFd());
		servers->addServer(*server);
	}

	return new Webserver(*kqueue, *servers, *config);
}

int main(int argc, char* argv[]) {
	atexit(leak);
	WebserverConfig* config = initializeConfig();
	std::cout << "WebserverConfig initialized" << std::endl;
	std::cout << "HTTPConfig: " << config->getHTTPConfig().getServers().size() << std::endl;
	std::cout << "Worker connections: " << config->getWorkerConnections() << std::endl;

	std::cout << "ServerConfig: " << config->getHTTPConfig().getServers()[0].getServerName() << std::endl;
	std::cout << "Root: " << config->getHTTPConfig().getServers()[0].getRoot() << std::endl;
	std::cout << "Port: " << config->getHTTPConfig().getServers()[0].getPort() << std::endl;

	std::cout << std::endl;

	Webserver* webserver = dependencyInjection(config);
	webserver->start();

	delete webserver; // 메모리 해제
	delete config; // 메모리 해제
	return 0;
}
