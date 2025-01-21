#include "LocationConfig.hpp"

LocationConfig::LocationConfig(
	const std::string& root, 
	bool autoIndex, 
	const std::string& redirect,
	const std::vector<std::string>& allowMethod,
	const std::string& fastcgiPass,
	const std::vector<std::string>& fastcgiIndex
): 
root(root), 
autoIndex(autoIndex), 
redirect(redirect), 
allowMethod(allowMethod), 
fastcgiPass(fastcgiPass), fastcgiIndex(fastcgiIndex) {
	
}