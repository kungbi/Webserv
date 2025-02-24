#include "Request.hpp"

Request::Request(int fd) : fd_(fd), complete_(false) {}

bool Request::isComplete() const {
	return complete_;
}

void Request::appendData(const char* data, size_t length) {
	originalRequest_.append(data, length);

	if (originalRequest_.find("\r\n\r\n") != std::string::npos)
		complete_ = true;
}

bool Request::equalFd(int fd) const {
	return fd_ == fd;
}

int Request::getFd() const {
	return fd_;
}
