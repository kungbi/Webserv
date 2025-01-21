# include "Http.hpp"

bool ErrorPageDirValidCheck(std::map<std::string, std::vector<std::string> > directives)
{
	if (directives.count("error_page") == 0)
		return (false);
	if (directives["error_page"].size() < 2)
		return (false);
	std::string uri = directives["error_page"][0];
	if (uri[0] != '/')
		return (false);
	for (size_t i = 1; i < directives["error_page"].size(); ++i)
	{
		if (!IsStatusNumber(directives["error_page"][i]))
			return (false);
	}
	return (true);
}

bool IsStatusNumber(std::string str)
{
	std::vector<std::string> statusNumbers = StatusNumbers();

	for (size_t i = 0; i < statusNumbers.size(); ++i)
	{
		if (str == statusNumbers[i])
			return (true);
	}
	return (false);
}

std::vector<std::string> StatusNumbers()
{
	std::vector<std::string> ret;

	ret.push_back("505");
	ret.push_back("504");
	ret.push_back("503");
	ret.push_back("502");
	ret.push_back("501");
	ret.push_back("500");
	ret.push_back("417");
	ret.push_back("416");
	ret.push_back("415");
	ret.push_back("414");
	ret.push_back("413");
	ret.push_back("412");
	ret.push_back("411");
	ret.push_back("410");
	ret.push_back("409");
	ret.push_back("408");
	ret.push_back("407");
	ret.push_back("406");
	ret.push_back("405");
	ret.push_back("404");
	ret.push_back("403");
	ret.push_back("402");
	ret.push_back("401");
	ret.push_back("400");
	ret.push_back("307");
	ret.push_back("306");
	ret.push_back("305");
	ret.push_back("304");
	ret.push_back("303");
	ret.push_back("302");
	ret.push_back("301");
	ret.push_back("300");
	ret.push_back("206");
	ret.push_back("205");
	ret.push_back("204");
	ret.push_back("203");
	ret.push_back("202");
	ret.push_back("201");
	ret.push_back("200");
	ret.push_back("100");
	ret.push_back("101");
	return (ret);
}