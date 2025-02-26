#include "Response.hpp"
#include <iostream>

int main() {
	Response response = Response::Builder()
		.setProtocolVersion("HTTP/1.1")
		.setStatusCode(200)
		// .setReasonPhrase("OK")
		.setServer("Server")
		.setContentType("text/html")
		.setConnection("close")
		.setBody(
			"\n" 
			"<html>\n" 
			"<body>\n" 
				"<h1>Welcome to our website</h1>\n" 
			"</body>\n" 
			"</html>"
		)
		.build();

	std::cout << response.getResponse() << std::endl;

	return 0;
}