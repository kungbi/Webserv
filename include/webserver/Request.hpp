#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <iostream>
# include <string>
# include <map>
# include <vector>

enum RequestType {
	GET,
	POST,
	PUT,
	PATCH,
	DELETE,
};

class Request {
private:
	int fd_;

	bool complete_;
	std::string originalRequest_;

	// 파싱된 내용들 추가
	RequestType requestType_;
	std::string protocolVersion_;
	std::string hostName_;
	std::string target_;
	int port_;
	std::string connection_;
	size_t contentLength_;
	std::string accept_;



	Request();

public:
	Request(int fd);
	void test();

	bool isComplete() const;
	void appendData(const char* data, size_t length);

	bool equalFd(int fd) const;
	int getFd() const;

	const std::string& getOriginalRequest() const;

	void setRequestType(const std::string& type);
	void setTarget(const std::string& target);
	void setPort(const int port);
	void setProtocolVersion(const std::string& version);
	void setHostName(const std::string& host);
	void setConnection(const std::string& connection);
	void setContentLength(size_t length);
	void setAccept(const std::string& accept);
};

#endif