#ifndef WEBSERVER_HPP
# define WEBSERVER_HPP

# include <unordered_map>
# include <vector>
# include <string>
# include <iostream>
# include "Kqueue.hpp"
# include "Servers.hpp"
# include "WebserverConfig.hpp"

class Webserver {
private:
	Kqueue kqueue;
	Servers servers;

	void initializeServers(const WebserverConfig& config);
	void handleServerSocketEvent(int fd);
	void handleClientRequest(int fd);
	void processEvents(struct kevent& event);
	void connectClient(struct kevent& event);
	void processClientRequest(struct kevent& event);

public:
	Webserver(const WebserverConfig& config);
	void start();
};


#endif