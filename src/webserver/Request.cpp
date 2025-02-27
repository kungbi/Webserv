#include "Request.hpp"

Request::Request(int fd) : fd_(fd), complete_(false) {}

bool Request::isComplete() const {
	return complete_;
}

void Request::appendData(const char* data, size_t length) {
	if (this->complete_ == true)
		throw std::runtime_error("Request is already complete");

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

const std::string& Request::getOriginalRequest() const {
	return originalRequest_;
}

void Request::setRequestType(const std::string& type) {
	requestType_ = type;
}

void Request::setTarget(const std::string& target) {
	target_ = target;
}

void Request::setProtocolVersion(const std::string& version) {
	protocolVersion_ = version;
}

