#ifndef RESPONSES_HPP
# define RESPONSES_HPP

# include "Response.hpp"
# include <map>

class Responses {
private:
	std::map<int, Response*> responses_;

public:
	Responses();

	void addResponse(Response* response);
	size_t size() const;
	bool isExist(int fd) const;
};

#endif