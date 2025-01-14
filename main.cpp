#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "ConfigData.hpp"

int main()
{
	ConfigReader reader;
	ConfigParser parser;

	parser.Tokenize(reader.ReadFile("nginx.conf"));
	IConfigContext *root = new IConfigContext(NULL, MAIN);
	try {
		parser.Parser(parser.GetTokens(), root);
	} catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
		exit(1);
	}

	ConfigData data(root);

	try {
		data.SearchTree();
	}
	catch (std::exception &e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}