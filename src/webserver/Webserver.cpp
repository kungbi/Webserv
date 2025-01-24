#include "Webserver.hpp"

Webserver::Webserver(const WebserverConfig& config): kqueue(config.getWorkerConnections()) {
	initializeServers(config);
}
void Webserver::initializeServers(const WebserverConfig& config) {
	HTTPConfig& httpConfig = config.getHTTPConfig();

	for (std::vector<ServerConfig>::const_iterator it = httpConfig.getServers().begin(); it != httpConfig.getServers().end(); ++it) {
		ServerConfig serverConfig = *it;
		Server* server = servers.createServer(serverConfig);

		kqueue.addEvent(server->getSocketFd(), SERVER, *server); // Kqueue에 등록
		servers.addServer(*server);
	}
}

void Webserver::handleServerSocketEvent(int fd) {
	Server* server = servers.getServerForSocketFd(fd);
	if (server) {
		int clientFd = server->acceptClient(); // 클라이언트 FD 반환
		if (clientFd != -1) {
			kqueue.addEvent(clientFd, REQUEST, *server); // Kqueue에 등록
			std::cout << "Client FD: " << clientFd << " registered with Kqueue." << std::endl;
		} else {
			std::cerr << "Failed to accept client on FD: " << fd << std::endl;
		}
	} else {
		std::cerr << "No server found for server socket FD: " << fd << std::endl;
	}
}

void Webserver::handleClientRequest(int fd) {
	servers.handleRequest(fd);
	
	kqueue.removeEvent(fd, EVFILT_READ);
	close(fd);
	std::cout << "Connection closed for FD: " << fd << std::endl;
}

void Webserver::connectClient(struct kevent& event) {
	Server &server = ((EventInfo *) event.udata)->server;

	int clientFd = server.acceptClient();

	if (clientFd == -1)  {
		throw std::runtime_error("Failed to accept client");
	}

	kqueue.addEvent(clientFd, REQUEST, server);
}

void Webserver::processClientRequest(struct kevent& event) {
	Server &server = ((EventInfo *) event.udata)->server;
	int clientFd = event.ident;

	server.handleRequest(clientFd);

	// kqueue.removeEvent(clientFd, EVFILT_READ);
	// close(clientFd);
}

void Webserver::processEvents(struct kevent& event) {
	int fd = event.ident;
	int filter = event.filter;
	EventInfo* eventInfo = (EventInfo *) event.udata;

	std::cout << "Processing event for FD: " << fd << std::endl;

	if (eventInfo->type == SERVER) {
		connectClient(event);
	}

	if (eventInfo->type == REQUEST) {
		processClientRequest(event);
	}

	if (eventInfo->type == RESPONSE) {
		// processWriteEvent(fd); // WRITE 이벤트 처리
	}
}


void Webserver::start() {
	std::cout << "Webserver started." << std::endl;

	while (true) {
		struct kevent* event = kqueue.pollEvents();
		processEvents(*event); // 이벤트 처리

		// delete event->udata;
		delete event; // 메모리 해제
	}
}
