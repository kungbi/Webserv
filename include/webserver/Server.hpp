#ifndef SERvER_HPP
# define SERvER_HPP

# include <iostream>
# include <map>
# include "Socket.hpp"

class Server {
private:
	Socket serverSocket;
	std::map<std::string, std::string> serverConfig;

public:
	Server(const std::map<std::string, std::string>& config);
	int getSocketFd() const;
	int acceptClient();
	void handleRequest(int clientFd);
};


#endif