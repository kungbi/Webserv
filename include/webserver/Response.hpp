#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include <string>
# include <ctime>

class Response {
private:
	int fd_;

	// Status Line
	std::string protocolVersion_;
	int statusCode_;
	std::string reasonPhrase_;

	// Headers
	std::tm& date_;
	std::string server_;
	std::string contentType_;
	size_t contentLength_;
	std::string connection_;

	// Body
	std::string body_;

};

#endif