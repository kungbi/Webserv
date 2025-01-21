#ifndef SERVERS_HPP
# define SERVERS_HPP

# include <vector>
# include <memory>
# include <map>
# include <string>
# include "Server.hpp"

class Servers {
private:
	std::vector<Server*> serverList; // 서버 리스트 (raw pointer)

public:
	Servers();
	~Servers();

	Server* createServer(const ServerConfig& config);
	void addServer(Server &server);
	bool isServerSocketFd(int fd);
	Server* getServerForSocketFd(int fd);
	void handleRequest(int fd);
	size_t size() const;
	Server& getServer(size_t index);
};


#endif