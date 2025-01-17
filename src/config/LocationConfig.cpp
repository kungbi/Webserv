#include "LocationConfig.hpp"

LocationConfig::LocationConfig(const std::string& uri, const std::string& root, bool autoIndex, const std::string& redirect)
    : uri(uri), root(root), autoIndex(autoIndex), redirect(redirect) {}

std::string LocationConfig::getURI() const {
    return uri;
}

void LocationConfig::setURI(const std::string& uri) {
    this->uri = uri;
}

std::string LocationConfig::getRoot() const {
    return root;
}

void LocationConfig::setRoot(const std::string& root) {
    this->root = root;
}

bool LocationConfig::isAutoIndex() const {
    return autoIndex;
}

void LocationConfig::setAutoIndex(bool value) {
    autoIndex = value;
}

std::string LocationConfig::getRedirect() const {
    return redirect;
}

void LocationConfig::setRedirect(const std::string& redirect) {
    this->redirect = redirect;
}
