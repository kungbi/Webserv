#include "Socket.hpp"

void Socket::setSocketOptions() {
	int opt = 1;
	if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
		perror("Set socket options failed");
		closeSocket();
		exit(EXIT_FAILURE);
	}
}

void Socket::bindSocket() {
	if (bind(socketFd, reinterpret_cast<struct sockaddr*>(&address), sizeof(address)) == -1) {
		perror("Socket bind failed");
		closeSocket();
		exit(EXIT_FAILURE);
	}
}

void Socket::listenSocket(int backlog = 5) {
	if (listen(socketFd, backlog) == -1) {
		perror("Socket listen failed");
		closeSocket();
		exit(EXIT_FAILURE);
	}
}

void Socket::configureSocket(const std::string& ip, int port) {
	std::memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = inet_addr(ip.c_str());
}

Socket::Socket(const std::string& ip, int port) {
	// 소켓 생성
	socketFd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketFd == -1) {
		perror("Socket creation failed");
		exit(EXIT_FAILURE);
	}

	// 소켓 설정 및 상태 전환
	configureSocket(ip, port);
	setSocketOptions();
	bindSocket();
	listenSocket();
	std::cout << "Socket is now in listening state at " << ip << ":" << port << std::endl;
}

Socket::~Socket() {
	closeSocket();
}

int Socket::acceptConnection() {
	socklen_t addrLen = sizeof(address);
	int clientFd = accept(socketFd, reinterpret_cast<struct sockaddr*>(&address), &addrLen);
	if (clientFd == -1) {
		perror("Socket accept failed");
	} else {
		std::cout << "Accepted connection with FD: " << clientFd << std::endl;
	}
	return clientFd;
}

int Socket::getSocketFd() const {
	return socketFd;
}

void Socket::closeSocket() {
	if (socketFd != -1) {
		close(socketFd);
		socketFd = -1;
		std::cout << "Socket closed." << std::endl;
	}
}
