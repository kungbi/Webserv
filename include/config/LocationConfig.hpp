#ifndef LOCATIONCONFIG_HPP
# define LOCATIONCONFIG_HPP

# include <string>
# include <vector>
# include <map>

class LocationConfig {
private:
	std::string pattern;
	std::string root;
	std::vector<std::string> allowMethod;

	bool autoindex;
	std::map<int, std::string> redirect;

	/**
	 * CGI관련 변수들 추가
	*/
	std::string fastcgiPass;
	std::vector<std::string> fastcgiIndex;
	
	LocationConfig(void);

public:
	LocationConfig(
		const std::string& root, 
		bool autoIndex, 
		const std::string& redirect,
		const std::vector<std::string>& allowMethod,
		const std::string& fastcgiPass,
		const std::vector<std::string>& fastcgiIndex
	);
};

#endif // LOCATIONCONFIG_HPP
