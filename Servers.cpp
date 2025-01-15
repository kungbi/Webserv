#include <vector>
#include <memory>
#include <map>
#include <string>

class Servers {
private:
    std::vector<std::unique_ptr<Server>> serverList; // 서버 목록

public:
    Servers() = default;

    void addServer(const std::map<std::string, std::string>& config, Webserver* webserver) {
        serverList.emplace_back(std::make_unique<Server>(config, webserver));
    }

    bool isServerSocketFd(int fd) {
        for (const auto& server : serverList) {
            if (server->getSocketFd() == fd) {
                return true;
            }
        }
        return false;
    }

    Server* getServerForSocketFd(int fd) {
        for (const auto& server : serverList) {
            if (server->getSocketFd() == fd) {
                return server.get();
            }
        }
        return nullptr;
    }

    void handleRequest(int fd) {
        for (const auto& server : serverList) {
            if (server->isClientFd(fd)) {
                server->handleRequest(fd); // 해당 서버에서 요청 처리
                return;
            }
        }
        std::cerr << "No server found for FD: " << fd << std::endl;
    }

    size_t size() const {
        return serverList.size();
    }

    Server& getServer(size_t index) {
        if (index >= serverList.size()) {
            throw std::out_of_range("Server index out of range.");
        }
        return *serverList[index];
    }
};
