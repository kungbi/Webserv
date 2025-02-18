#ifndef SOCKET_HPP
# define SOCKET_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

class Socket {
private:
	int socketFd_;
	struct sockaddr_in address_;

	void setSocketOptions();
	void bindSocket();
	void listenSocket(int backlog);
	void configureSocket(const std::string& ip, int port);

	Socket(void);

public:
	Socket(const std::string& ip, int port);
	~Socket();

	int acceptConnection();
	int getSocketFd() const;
	void closeSocket();
};


#endif