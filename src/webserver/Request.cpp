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

RequestType Request::getRequestType() const {
	return requestType_;
}

std::string Request::getProtocolVersion() const {
	return protocolVersion_;
}

std::string Request::getHostName() const {
	return hostName_;
}

int Request::getPort() const {
	return port_;
}

std::string Request::getConnection() const {
	return connection_;
}

size_t Request::getContentLength() const {
	return contentLength_;
}

std::string Request::getAccept() const {
	return accept_;
}

std::string Request::getTarget() const {
	return target_;
}

std::string Request::getQuery() const {
	return query_;
}

std::string Request::getFilename() const {
	return fileName_;
}

std::string Request::getExtension() const {
	return extension_;
}


void Request::setRequestType(const std::string& type) {
	if (type == "GET")
		requestType_ = GET;
	else if (type == "POST")
		requestType_ = POST;
	else if (type == "PUT")
		requestType_ = PUT;
	else if (type == "PATCH")
		requestType_ = PATCH;
	else if (type == "DELETE")
		requestType_ = DELETE;
	else
		throw std::runtime_error("Invalid request type");
}

void Request::setTarget(const std::string& target) {
	target_ = target;
}

void Request::setProtocolVersion(const std::string& version) {
	protocolVersion_ = version;
}

void Request::setPort(const int port)
{
	port_ = port;
}

void Request::setConnection(const std::string& connection)
{
	connection_ = connection;
}

void Request::setHostName(const std::string& hostName)
{
	hostName_ = hostName;
}

void Request::setAccept(const std::string& accept)
{
	accept_ = accept;
}

void Request::setContentLength(size_t length) {
	contentLength_ = length;
}

void Request::setQuery(const std::string& query) { 
	query_ = query;
}

void Request::setFilename(const std::string& filename) {
	fileName_ = filename;
}

void Request::setExtension(const std::string& extension) {
	extension_ = extension;
}

// void Request::test()
// {
// 	std::cout << "Type : ";
// 	switch (requestType_) {
// 		case GET:    std::cout << "GET"; break;
// 		case POST:   std::cout << "POST"; break;
// 		case PUT:    std::cout << "PUT"; break;
// 		case PATCH:  std::cout << "PATCH"; break;
// 		case DELETE: std::cout << "DELETE"; break;
// 	}
// 	std::cout << std::endl;
// 	std::cout<<"protocolVersion : "<< protocolVersion_ << std::endl;
// 	std::cout<<"hostName_ : "<< hostName_ << std::endl;
// 	std::cout<<"portNumber : "<< port_ << std::endl;
// 	std::cout<<"target : "<< target_ << std::endl;
// 	std::cout<<"connection : " << connection_ << std::endl;
// 	std::cout<<"accept : " << accept_ << std::endl;
// 	std::cout<<"content-length : " << contentLength_<<std::endl;
// }