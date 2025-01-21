#ifndef LOCATIONCONFIG_HPP
#define LOCATIONCONFIG_HPP

#include <string>
#include <vector>

class LocationConfig {
private:
	std::string root;         // 루트 디렉토리
	bool autoIndex;           // 디렉토리 인덱싱 허용 여부
	std::string redirect;     // 리다이렉트 경로
	std::vector<std::string> allowMethod;

	/**
	 * CGI관련 변수들 추가
	*/
	std::string fastcgiPass;
	std::vector<std::string> fastcgiIndex;
	
	LocationConfig();

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
