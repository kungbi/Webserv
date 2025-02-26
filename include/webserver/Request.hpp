#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>

class Request {
private:
	int fd_;

	bool complete_;
	std::string originalRequest_;

	// 파싱된 내용들 추가
	std::string request_type;
	std::string http_ver;
	std::string host_name;
	std::string host_port;
	std::string connection;
	int content_length;


	Request();

public:
	Request(int fd);

	bool isComplete() const;
	void appendData(const char* data, size_t length);

	bool equalFd(int fd) const;
	int getFd() const;
};

#endif