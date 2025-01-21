#include "ServerConfig.hpp"

ServerConfig::ServerConfig(
	const std::string& serverName, 
	const std::string& root, 
	int port, 
	const std::vector<std::string>& index, 
	int client_max_body_size, 
	const std::map<std::string, std::string>& errorPages,
	const std::map<std::string, LocationConfig>& exactLocations,
	const std::map<std::string, LocationConfig>& prefixLocations,
	const std::map<std::string, LocationConfig>& regexLocations)
	:
	serverName(serverName),
	root(root), 
	port(port), 
	index(index), 
	client_max_body_size(client_max_body_size), 
	errorPages(errorPages), 
	exactLocations(exactLocations), 
	prefixLocations(prefixLocations), 
	regexLocations(regexLocations) {
	
	if (!(1 <= port && port <= 65535)) {
		throw std::invalid_argument("Invalid port number");
	}

	if (root.empty()) {
		throw std::invalid_argument("Root directory is empty");
	}

	if (serverName.empty()) {
		throw std::invalid_argument("Server name is empty");
	}

	if (index.empty()) {
		throw std::invalid_argument("Index is empty");
	}

	if (client_max_body_size < 1) {
		throw std::invalid_argument("Invalid client_max_body_size");
	}
}

std::string ServerConfig::getServerName() const {
	return serverName;
}

std::string ServerConfig::getRoot() const {
	return root;
}

int ServerConfig::getPort() const {
	return port;
}

std::vector<std::string> ServerConfig::getIndex() const {
	return index;
}

int ServerConfig::getClientMaxBodySize() const {
	return client_max_body_size;
}

std::map<std::string, std::string> ServerConfig::getErrorPages() const {
	return errorPages;
}

std::map<std::string, LocationConfig> ServerConfig::getExactLocations() const {
	return exactLocations;
}

std::map<std::string, LocationConfig> ServerConfig::getPrefixLocations() const {
	return prefixLocations;
}

std::map<std::string, LocationConfig> ServerConfig::getRegexLocations() const {
	return regexLocations;
}

