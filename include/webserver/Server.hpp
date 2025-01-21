#ifndef SERvER_HPP
# define SERvER_HPP

# include <iostream>
# include <map>
# include "Socket.hpp"
# include "ServerConfig.hpp"

class Server {
private:
	Socket serverSocket;
	const ServerConfig& serverConfig;

public:
	Server(const ServerConfig& config);
	int getSocketFd() const;
	int acceptClient();
	void handleRequest(int clientFd);
};


#endif