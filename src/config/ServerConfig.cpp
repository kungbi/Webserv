#include "ServerConfig.hpp"

ServerConfig::ServerConfig(const std::string& name, const std::string& root, int port)
    : serverName(name), root(root), port(port) {}

std::string ServerConfig::getServerName() const {
    return serverName;
}

void ServerConfig::setServerName(const std::string& name) {
    serverName = name;
}

std::string ServerConfig::getRoot() const {
    return root;
}

void ServerConfig::setRoot(const std::string& root) {
    this->root = root;
}

int ServerConfig::getPort() const {
    return port;
}

void ServerConfig::setPort(int port) {
    this->port = port;
}

void ServerConfig::addLocation(const LocationConfig& location) {
    locations.push_back(location);
}

const std::vector<LocationConfig>& ServerConfig::getLocations() const {
    return locations;
}
