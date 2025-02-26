#include "Response.hpp"
#include <iostream>

int main() {
	Response response = Response::Builder()
		.setFd(1)
		.setProtocolVersion("HTTP/1.1")
		.setStatusCode(200)
		.setReasonPhrase("OK")
		.setServer("Server")
		.setContentType("text/html")
		.setConnection("close")
		.setBody("HTTP/1.1 200 OK\n" 
			"Content-Type: text/html\n" 
			"Content-Length: 102\n" 
			"\n" 
			"<html>\n" 
			"<body>\n" 
				"<h1>Welcome to our website</h1>\n" 
			"</body>\n" 
			"</html>")
		.build();

	std::cout << response.getResponse() << std::endl;

	return 0;
}