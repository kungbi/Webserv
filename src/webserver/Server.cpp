#include "Server.hpp"

Server::Server(const ServerConfig& config)
	: serverSocket("127.0.0.1", config.getPort()),
	  serverConfig(config) {
	std::cout << "Server initialized at " << serverConfig.getServerName() << ":" << serverConfig.getPort() << std::endl;
}

int Server::getSocketFd() const {
	return serverSocket.getSocketFd();
}

int Server::acceptClient() {
	return serverSocket.acceptConnection(); // 클라이언트 요청을 수락하고 FD 반환
}

void Server::handleRequest(int clientFd) {
	std::cout << "Handling request for client FD: " << clientFd << std::endl;
	// 요청 처리 로직 추가
}
