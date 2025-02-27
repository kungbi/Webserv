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
	std::string requestType_;
	std::string protocolVersion_;
	std::string hostName_;
	std::string port_;
	std::string connection_;
	size_t contentLength_;
	std::map<double, std::vector<std::string>, std::greater<double> > acceptTypes_;



	Request();

public:
	Request(int fd);

	bool isComplete() const;
	void appendData(const char* data, size_t length);

	bool equalFd(int fd) const;
	int getFd() const;

	std::string getOriginalRequest() const;

	void setRequestType(const std::string& type);
	void setPortNumber(const std::string& portNumber);
	void setProtocolVersion(const std::string& version);
	void setHostName(const std::string& host);
	void setConnection(const std::string& connection);
	void setContentLength(size_t length);
	void setAcceptTypes(const std::map<double, std::vector<std::string>, std::greater<double> >& types);
};

#endif