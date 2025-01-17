#include "Server.hpp"

Server::Server(const std::map<std::string, std::string>& config)
	: serverSocket(config.at("ip"), std::stoi(config.at("port"))),
	  serverConfig(config) {
	std::cout << "Server initialized at " << config.at("ip") << ":" << config.at("port") << std::endl;
}

int Server::getSocketFd() const {
	return serverSocket.getSocketFd();
}

int Server::acceptClient() {
	return serverSocket.acceptConnection(); // 클라이언트 요청을 수락하고 FD 반환
}

void Server::handleRequest(int clientFd) {
	std::cout << "Handling request on FD: " << clientFd << " at Server "
			  << serverConfig.at("ip") << ":" << serverConfig.at("port") << std::endl;
	// 요청 처리 로직 추가
}
