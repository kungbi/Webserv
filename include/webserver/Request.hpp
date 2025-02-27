#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>

class Request {
private:
	int fd_;

	bool complete_;
	std::string originalRequest_;

	// 파싱된 내용들 추가
	std::string request_type;
	std::string protocolVersion;
	std::string hostName;
	std::string port;
	std::string connection;
	size_t contentLength;
	std::map<double, std::vector<std::string>, std::greater<double> > acceptTypes;



	Request();

public:
	Request(int fd);

	bool isComplete() const;
	void appendData(const char* data, size_t length);

	bool equalFd(int fd) const;
	int getFd() const;
};

#endif