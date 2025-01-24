#include "Server.hpp"

Server::Server(Socket& serverSocket, ServerConfig& serverConfig, Kqueue& kqueue)
	: serverSocket_(serverSocket), serverConfig_(serverConfig), kqueue_(kqueue) {
	std::cout << "Server initialized at " << serverConfig.getServerName() << ":" << serverConfig.getPort() << std::endl;
}

int Server::getSocketFd() const {
	return serverSocket_.getSocketFd();
}

int Server::acceptClient() {
	return serverSocket_.acceptConnection(); // 클라이언트 요청을 수락하고 FD 반환
}

int Server::handleRequest(int clientFd) {
	std::cout << "Handling request for client FD: " << clientFd << std::endl;

	// 클라이언트 요청 처리
	char buffer[1025];
	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	std::cout << "Bytes read: " << bytesRead << std::endl;

	if (bytesRead > 0) {
		buffer[bytesRead] = '\0'; // Null-terminate for safety
		std::cout << "Received: " << buffer << " from FD: " << clientFd << std::endl;

		const char* response = 
			"HTTP/1.1 200 OK\r\n"
			"Content-Length: 12\r\n"
			"Connection: close\r\n"
			"\r\n"
			"Hello World\n";
		send(clientFd, response, strlen(response), 0);
		return 0;
	} else if (bytesRead == 0) {
		// 클라이언트가 연결을 닫은 경우
		std::cout << "Client disconnected on FD: " << clientFd << std::endl;
		// kqueue.removeEvent(fd, EVFILT_READ); // Kqueue에서 제거
		close(clientFd); // 소켓 닫기
	} else {
		// 읽기 실패 (에러 처리)
		perror("Error reading from FD");
		// kqueue.removeEvent(clientFd, EVFILT_READ); // Kqueue에서 제거
		close(clientFd); // 소켓 닫기
	}
	return 1;
}
