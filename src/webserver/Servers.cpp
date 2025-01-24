#include "Servers.hpp"

Servers::Servers(Kqueue& kqueue): kqueue(kqueue) {}

Servers::~Servers() {
	for (size_t i = 0; i < serverList.size(); ++i) {
		delete serverList[i]; // 서버 객체 삭제
	}
}

Server* Servers::createServer(Socket& socket, ServerConfig& config, Kqueue& kqueue) {
	return new Server(socket, config, kqueue);
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
	std::cout << "Getting server for FD: " << fd << std::endl;
	for (size_t i = 0; i < serverList.size(); ++i) {
		std::cout << "Server FD: " << serverList[i]->getSocketFd() << std::endl;
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

int Servers::connectClient(int serverFd) {
	Server* server = getServerForSocketFd(serverFd);
	if (server == nullptr) {
		throw std::runtime_error("No server found for server FD");
	}

	int clientFd = server->acceptClient();
	if (clientFd == -1) {
		throw std::runtime_error("Failed to accept client");
	}
	return clientFd;
}

int Servers::processRequest(int serverFd, int clientFd) {
	Server* server = getServerForSocketFd(serverFd);
	if (!server) {
		throw std::runtime_error("No server found for client FD");
	}

	int result = server->handleRequest(clientFd);
	kqueue.removeEvent(clientFd, EVFILT_READ);
	close(clientFd);

	return result;
}