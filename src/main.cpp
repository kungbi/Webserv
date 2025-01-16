#include "Webserver.hpp"

int main(int argc, char* argv[]) {
	Webserver webserver("config.conf");
	webserver.start();

	return 0;
}