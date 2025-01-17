#include "Servers.hpp"

Servers::Servers() {}

Servers::~Servers() {
	for (size_t i = 0; i < serverList.size(); ++i) {
		delete serverList[i]; // 서버 객체 삭제
	}
}

Server* Servers::createServer(const std::map<std::string, std::string>& config) {
	return new Server(config);
}

void Servers::addServer(Server &server) {
	serverList.push_back(&server);
}

bool Servers::isServerSocketFd(int fd) {
	std::cout << "Checking for FD: " << fd << std::endl;

	for (size_t i = 0; i < serverList.size(); ++i) {
		std::cout << "Server FD: " << serverList[i]->getSocketFd() << std::endl;
		if (serverList[i]->getSocketFd() == fd) {
			return true;
		}
	}
	return false;
}

Server* Servers::getServerForSocketFd(int fd) {
	for (size_t i = 0; i < serverList.size(); ++i) {
		if (serverList[i]->getSocketFd() == fd) {
			return serverList[i];
		}
	}
	return nullptr;
}

void Servers::handleRequest(int fd) {
	const char* response = 
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 12\r\n"
		"Connection: close\r\n"
		"\r\n"
		"Hello World\n";

	write(fd, response, strlen(response));
}

size_t Servers::size() const {
	return serverList.size();
}

Server& Servers::getServer(size_t index) {
	if (index >= serverList.size()) {
		throw std::out_of_range("Server index out of range.");
	}
	return *serverList[index];
}
