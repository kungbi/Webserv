#include "Webserver.hpp"
#include "WebserverConfig.hpp"
#include "ServerConfig.hpp"
#include "HTTPConfig.hpp"
#include "LocationConfig.hpp"

WebserverConfig* initializeConfig() {
	// Location1 생성
	std::vector<std::string> location1Methods;
	location1Methods.push_back("GET");
	location1Methods.push_back("POST");

	std::map<int, std::string> location1Redirect;
	location1Redirect[301] = "/redirected";

	std::vector<std::string> location1Index;
	location1Index.push_back("index.html");

	LocationConfig location1(
		"/", "/var/www/html", location1Methods, false, location1Redirect, location1Index, ""
	);

	// ServerConfig1 생성
	std::map<int, std::string> server1ErrorPages;
	server1ErrorPages[404] = "/404.html";
	server1ErrorPages[500] = "/50x.html";
	server1ErrorPages[501] = "/50x.html";
	server1ErrorPages[502] = "/50x.html";

	std::vector<LocationConfig> server1Locations;
	server1Locations.push_back(location1);
	
	
	ServerConfig serverConfig1(
		"0.0.0.0", 8080, "localhost", 10, server1ErrorPages, server1Locations, true
	);

	// HTTPConfig 인스턴스 생성
	std::vector<ServerConfig> servers;
	servers.push_back(serverConfig1);

	HTTPConfig httpConfig(servers);

	// WebserverConfig 인스턴스 생성
	return new WebserverConfig(httpConfig);
}

#include <stdlib.h>

void leak() {
	system("leaks webserv");
}

Webserver* dependencyInjection(WebserverConfig* config) {
	Kqueue* kqueue = new Kqueue(1024);
	Servers* servers = new Servers(*kqueue);
	for (std::vector<ServerConfig>::const_iterator it = config->getHTTPConfig().getServers().begin(); it != config->getHTTPConfig().getServers().end(); ++it) {
		ServerConfig serverConfig = *it;
		Socket* serverSocket = new Socket(serverConfig.getHost(), serverConfig.getPort());
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

	std::cout << "ServerConfig: " << config->getHTTPConfig().getServers()[0].getServerName() << std::endl;
	std::cout << "Port: " << config->getHTTPConfig().getServers()[0].getPort() << std::endl;

	std::cout << std::endl;

	Webserver* webserver = dependencyInjection(config);
	webserver->start();

	delete webserver; // 메모리 해제
	delete config; // 메모리 해제
	return 0;
}
