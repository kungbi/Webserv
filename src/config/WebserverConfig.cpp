#include "WebserverConfig.hpp"

WebserverConfig::WebserverConfig() {}

HTTPConfig& WebserverConfig::getHTTPConfig() {
    return httpConfig;
}

const HTTPConfig& WebserverConfig::getHTTPConfig() const {
    return httpConfig;
}

void WebserverConfig::addServer(const ServerConfig& server) {
    servers.push_back(server);
}

const std::vector<ServerConfig>& WebserverConfig::getServers() const {
    return servers;
}
