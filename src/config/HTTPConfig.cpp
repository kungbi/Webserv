#include "HTTPConfig.hpp"

HTTPConfig::HTTPConfig(const std::string& serverHeader, bool keepAlive, size_t maxRequestSize)
    : serverHeader(serverHeader), keepAlive(keepAlive), maxRequestSize(maxRequestSize) {}

std::string HTTPConfig::getServerHeader() const {
    return serverHeader;
}

void HTTPConfig::setServerHeader(const std::string& header) {
    serverHeader = header;
}

bool HTTPConfig::isKeepAlive() const {
    return keepAlive;
}

void HTTPConfig::setKeepAlive(bool value) {
    keepAlive = value;
}

size_t HTTPConfig::getMaxRequestSize() const {
    return maxRequestSize;
}

void HTTPConfig::setMaxRequestSize(size_t size) {
    maxRequestSize = size;
}
