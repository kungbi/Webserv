#include "WebserverConfig.hpp"

WebserverConfig::WebserverConfig(const HTTPConfig& httpConfig, int workerConnections)
	: httpConfig(httpConfig), workerConnections(workerConnections) {
	if (workerConnections < 1) {
		throw std::invalid_argument("workerConnections must be greater than 0");
	}
}

HTTPConfig& WebserverConfig::getHTTPConfig() const {
	return const_cast<HTTPConfig&>(httpConfig);
}

int WebserverConfig::getWorkerConnections() const {
	return workerConnections;
}