#ifndef REQUEST_PARSER_HPP
# define REQUEST_PARSER_HPP

# include <sstream>


class Request;  // forward declaration

class RequestParser {
    public:
        void parseRequestHeader(Request* request);
};

#endif