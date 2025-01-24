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
	Kqueue& kqueue;
	Servers& servers;
	WebserverConfig& config;

	void processEvents(struct kevent& event);
	void connectClient(struct kevent& event);
	void processClientRequest(struct kevent& event);

public:
	Webserver(Kqueue& kqueue, Servers& servers, WebserverConfig& config);
	void start();
};


#endif