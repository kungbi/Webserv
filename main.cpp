#include "ConfigParser.hpp"
#include "ConfigReader.hpp"
#include "ConfigData.hpp"

int main()
{
	ConfigReader reader;
	ConfigParser parser;

	parser.Tokenize(reader.ReadFile("nginx.conf"));
	IConfigContext *root = new IConfigContext(NULL, MAIN);
	parser.Parser(parser.GetTokens(), root);

	ConfigData data(root);

	data.SearchTree();
	return (0);
}