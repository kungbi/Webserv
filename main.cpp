#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "ConfigData.hpp"

int main()
{
	ConfigReader reader;
	ConfigParser parser;

	parser.Tokenize(reader.ReadFile("nginx.conf"));
	IConfigContext *root = parser.Parser();
	if (root == NULL)
		std::cerr << "Parsing Error!" << std::endl;

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