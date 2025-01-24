#include "Webserver.hpp"

Webserver::Webserver(Kqueue& kqueue, Servers& servers, WebserverConfig& config)
	: kqueue(kqueue), servers(servers), config(config) {}
	
void Webserver::connectClient(struct kevent& event) {
	int serverFd = ((EventInfo *) event.udata)->serverFd;
	int clientFd = servers.connectClient(serverFd);

	if (clientFd == -1)  {
		throw std::runtime_error("Failed to accept client");
	}

	kqueue.addEvent(clientFd, REQUEST, serverFd);
}

void Webserver::processClientRequest(struct kevent& event) {
	int serverFd = ((EventInfo *) event.udata)->serverFd;
	int clientFd = event.ident;

	servers.processRequest(serverFd, clientFd);
}

void Webserver::processEvents(struct kevent& event) {
	int fd = event.ident;
	EventInfo* eventInfo = (EventInfo *) event.udata;

	std::cout << "Processing event for FD: " << fd << std::endl;

	if (eventInfo->type == SERVER) {
		std::cout << "Server event." << std::endl;
		connectClient(event);
	}

	if (eventInfo->type == REQUEST) {
		std::cout << "Request event." << std::endl;
		processClientRequest(event);
		delete event.udata;
	}

	if (eventInfo->type == RESPONSE) {
	}

}

void Webserver::start() {
	std::cout << "Webserver started." << std::endl << std::endl;

	while (true) {
		struct kevent* event = kqueue.pollEvents();
		processEvents(*event); // 이벤트 처리
		std::cout << "================" << std::endl;

		delete event; // 메모리 해제
	}
}
