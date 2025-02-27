#include "requestParser.hpp"
#include "Request.hpp"

void RequestParser::parseRequestHeader(Request *request)
{
    const std::string& originalRequest = request->getOriginalRequest();
    std::cout<<"In Parse Class" << std::endl;
    std::cout<<originalRequest<<std::endl;

    std::istringstream stream(originalRequest);
    std::string line;

    // 1️⃣ 첫 번째 줄 (요청 라인) 파싱
    if (std::getline(stream, line)) {
        std::istringstream lineStream(line);
        std::string method, target, version;
        lineStream >> method >> target >> version;
        request->setRequestType(method);
        request->setTarget(target);
        request->setProtocolVersion(version);
    }

}