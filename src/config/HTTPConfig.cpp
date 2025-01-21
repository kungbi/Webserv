#include "HTTPConfig.hpp"

HTTPConfig::HTTPConfig(std::vector<ServerConfig>& servers) : servers(servers) {}

std::vector<ServerConfig>& HTTPConfig::getServers() {
	return servers;
}