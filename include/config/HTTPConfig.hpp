#ifndef HTTPCONFIG_HPP
# define HTTPCONFIG_HPP

# include <string>
# include <vector>
# include "ServerConfig.hpp"

class HTTPConfig {
private:
	std::vector<ServerConfig> servers;

	HTTPConfig(void);

public:
	HTTPConfig(std::vector<ServerConfig>& servers);

	std::vector<ServerConfig>& getServers();
};

#endif // HTTPCONFIG_HPP
