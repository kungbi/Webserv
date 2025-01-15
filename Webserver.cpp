#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>

class Webserver {
private:
    Kqueue kqueueManager;                      // Kqueue 관리
    Servers servers;                           // 여러 Server 관리

    void initializeServers(const std::string& configFile) {
        // 예제 서버 설정
        std::map<std::string, std::string> server1Config = {{"ip", "127.0.0.1"}, {"port", "8080"}};
        std::map<std::string, std::string> server2Config = {{"ip", "127.0.0.1"}, {"port", "9090"}};

        servers.addServer(server1Config);
        servers.addServer(server2Config);
    }

    void registerFd(int clientFd) {
        kqueueManager.addFd(clientFd, EVFILT_READ); // Kqueue에 등록
        std::cout << "Client FD: " << clientFd << " registered with Kqueue." << std::endl;
    }

    void handleServerSocketEvent(int fd) {
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

    void handleClientRequest(int fd) {
        servers.handleRequest(fd); // 서버를 통해 요청 처리
    }

    void processEvents(const std::vector<std::pair<int, int>>& events) {
        for (const auto& [fd, filter] : events) {
            if (filter == EVFILT_READ) {
                processReadEvent(fd); // READ 이벤트 처리
            }
        }
    }

    void processReadEvent(int fd) {
        if (servers.isServerSocketFd(fd)) {
            handleServerSocketEvent(fd); // 서버 소켓 이벤트 처리
        } else {
            handleClientRequest(fd); // 클라이언트 요청 처리
        }
    }

public:
    Webserver(const std::string& configFile) {
        initializeServers(configFile);
    }

    void start() {
        std::cout << "Webserver started." << std::endl;

        while (true) {
            auto events = kqueueManager.pollEvents();
            processEvents(events); // 이벤트 처리
        }
    }
};
