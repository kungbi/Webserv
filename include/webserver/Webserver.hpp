#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <unordered_map>
# include <vector>
# include <string>
# include <iostream>
# include "Kqueue.hpp"
# include "Servers.hpp"

class Webserver {
private:
	Kqueue kqueueManager;
	Servers servers;

	void initializeServers(const std::string& configFile);
	void registerFd(int clientFd);
	void handleServerSocketEvent(int fd);
	void handleClientRequest(int fd);
	void processEvents(const std::vector< std::pair<int, int> >& events);
	void processReadEvent(int fd);

public:
	Webserver(const std::string& configFile);
	void start();
};


#endif