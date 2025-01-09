#include "ConfigParser.hpp"
#include "ConfigReader.hpp"

int main()
{
	ConfigReader reader;
	ConfigParser parser;

	parser.Tokenize(reader.ReadFile("nginx.conf"));
	return (0);
}