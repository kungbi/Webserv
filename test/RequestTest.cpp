#include "Request.hpp"

int main() {
	Request request(5);
	request.appendData("GET / HTTP/1.1\r\nHost: localhost:8080\r\n\r\n", 40);
	std::cout << "Request complete: " << request.isComplete() << std::endl;


	Request request2(5);
	request2.appendData("GET / HTTP/1.1\r\nHost: localhost:8080", 36);
	std::cout << "Request complete: " << request2.isComplete() << std::endl;

	return 0;
}