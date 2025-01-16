#include "Webserver.hpp"

void Webserver::initializeServers(const std::string& configFile) {
	configFile.c_str();

    // 예제 서버 설정
    std::map<std::string, std::string> server1Config;
    server1Config.insert(std::make_pair("ip", "127.0.0.1"));
    server1Config.insert(std::make_pair("port", "8080"));

    std::map<std::string, std::string> server2Config;
    server2Config.insert(std::make_pair("ip", "127.0.0.1"));
    server2Config.insert(std::make_pair("port", "9090"));

    servers.addServer(server1Config);
    servers.addServer(server2Config);
}

void Webserver::registerFd(int clientFd) {
    kqueueManager.addFd(clientFd, EVFILT_READ, EV_ADD | EV_ENABLE); // Kqueue에 등록
    std::cout << "Client FD: " << clientFd << " registered with Kqueue." << std::endl;
}

void Webserver::handleServerSocketEvent(int fd) {
    Server* server = servers.getServerForSocketFd(fd);
    if (server) {
        int clientFd = server->acceptClient(); // 클라이언트 FD 반환
        if (clientFd != -1) {
            registerFd(clientFd); // 클라이언트 FD를 Kqueue에 등록
        } else {
            std::cerr << "Failed to accept client on FD: " << fd << std::endl;
        }
    } else {
        std::cerr << "No server found for server socket FD: " << fd << std::endl;
    }
}

void Webserver::handleClientRequest(int fd) {
    servers.handleRequest(fd); // 서버를 통해 요청 처리
}

void Webserver::processEvents(const std::vector<std::pair<int, int> >& events) {
    for (std::vector<std::pair<int, int> >::const_iterator it = events.begin(); it != events.end(); ++it) {
        int fd = it->first;
        int filter = it->second;
        if (filter == EVFILT_READ) {
            processReadEvent(fd); // READ 이벤트 처리
        }
    }
}

void Webserver::processReadEvent(int fd) {
    if (servers.isServerSocketFd(fd)) {
        handleServerSocketEvent(fd); // 서버 소켓 이벤트 처리
    } else {
        handleClientRequest(fd); // 클라이언트 요청 처리
    }
}

Webserver::Webserver(const std::string& configFile) {
    initializeServers(configFile);
}

void Webserver::start() {
    std::cout << "Webserver started." << std::endl;

    while (true) {
        std::vector<std::pair<int, int> > events = kqueueManager.pollEvents(10, -1); // 인수 추가
        processEvents(events); // 이벤트 처리
    }
}
