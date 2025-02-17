#include "LocationConfig.hpp"

LocationConfig::LocationConfig(
    const std::string pattern,
    const std::string root,	
    const std::vector<std::string>& allowMethod,
    const bool autoindex,
    const std::map<int, std::string>& redirect,
    const std::vector<std::string>& index,
    const std::string cgiInterpreter
) 
    : pattern(pattern), 
      root(root), 
      allowMethod(allowMethod), 
      autoindex(autoindex), 
      redirect(redirect), 
      index(index), 
      cgiInterpreter(cgiInterpreter) 
{}
