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

	Request();

public:
	Request(int fd);

	bool isComplete() const;
	void appendData(const char* data, size_t length);

	bool equalFd(int fd) const;
	int getFd() const;
};

#endif