#include "Servers.hpp"

Servers::Servers() {}

Servers::~Servers() {
    for (size_t i = 0; i < serverList.size(); ++i) {
        delete serverList[i]; // 서버 객체 삭제
    }
}

void Servers::addServer(const std::map<std::string, std::string>& config) {
    serverList.push_back(new Server(config)); // raw pointer 사용
}

bool Servers::isServerSocketFd(int fd) {
    for (size_t i = 0; i < serverList.size(); ++i) {
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
    std::cerr << "No server found for FD: " << fd << std::endl;
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
