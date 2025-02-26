#include "Responses.hpp"

Responses::Responses() {}

void Responses::addResponse(const Response& response) {
	if (isExist(response.getFd()) {
		throw std::runtime_error("Response already exists");
	})
	responses_[response.getFd()] = new Response(response);
}

size_t Responses::size() const {
	return responses_.size();
}

bool Responses::isExist(int fd) const {
	return responses_.find(fd) != responses_.end();
}