#include "Server.hpp"
#include "Request.hpp"

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

int Server::processClientData(int clientFd, const char* buffer, ssize_t bytesRead) {
	std::cout << "Received: " << buffer << " from FD: " << clientFd << std::endl;

	if (!this->requests_.isExist(clientFd)) {
		this->requests_.addRequest(new Request(clientFd));
	}
	Request* request = this->requests_.getRequest(clientFd);
	request->appendData(buffer, bytesRead);

	if (request->isComplete()) {
		requestParser_.parseRequestHeader(request);
		Response response = Response::Builder()
			.setProtocolVersion("HTTP/1.1")
			.setStatusCode(200)
			.setReasonPhrase("OK")
			.setServer("Server")
			.setContentType("text/html")
			.setConnection("close")
			.setBody(
				"<html>\n" 
				"<body>\n" 
					"<h1>Welcome to our website</h1>\n" 
				"</body>\n" 
				"</html>"
			)
			.build();
		
		sendResponse(clientFd, response.getResponse());
		this->requests_.removeRequest(clientFd);
		return 0;
	}

	return 2;
}

void Server::sendResponse(int clientFd, const std::string& response) {
	send(clientFd, response.c_str(), response.size(), 0);
}

int Server::handleRequest(int clientFd) { // <- 함수 분리 전
	std::cout << "Handling request for client FD: " << clientFd << std::endl;

	// 클라이언트 요청 처리
	char buffer[1025];
	ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
	std::cout << "Bytes read: " << bytesRead << std::endl;

	if (bytesRead > 0) {
		buffer[bytesRead] = '\0'; // Null-terminate for safety
		return processClientData(clientFd, buffer, bytesRead);
	}
	
	if (bytesRead == 0) {
		// 클라이언트가 연결을 닫은 경우
		std::cout << "Client disconnected on FD: " << clientFd << std::endl;
		// kqueue.removeEvent(fd, EVFILT_READ); // Kqueue에서 제거
		close(clientFd); // 소켓 닫기
		return 1;
	}
	
	perror("Error reading from FD");
	// kqueue.removeEvent(clientFd, EVFILT_READ); // Kqueue에서 제거
	close(clientFd); // 소켓 닫기
	return 1;
}


