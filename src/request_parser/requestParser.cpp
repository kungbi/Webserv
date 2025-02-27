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
        request->setProtocolVersion(version);

        UriComponents uri = RequestParser::parseUri(target);
        request->setTarget(uri.path);
        request->setQuery(uri.query);
        request->setFilename(uri.filename);
        request->setExtension(uri.extension);
    }
    while (std::getline(stream, line) && !line.empty()) {
        size_t colonPos = line.find(":");
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 2); // ": " 이후 값 추출

            if (key == "Host") {
                size_t colonPos = value.find(":");
                if (colonPos != std::string::npos) {
                    std::string host = value.substr(0, colonPos);
                    std::string port = value.substr(colonPos + 1);
                    request->setHostName(host);
                    request->setPort(std::stoul(port));
                }
                else
                    request->setHostName(value);
            } else if (key == "Connection") {
                request->setConnection(value);
            } else if (key == "Content-Length") {
                request->setContentLength(std::stoul(value));
            } else if (key == "Accept") {
                request->setAccept(value);  // `Accept` 헤더 전체를 저장
            }
        }
    }
    
}

UriComponents RequestParser::parseUri(const std::string& target) {
    UriComponents result;
    
    // ✅ 1️⃣ 쿼리 문자열 분리
    size_t queryPos = target.find("?");
    if (queryPos != std::string::npos) {
        result.path = target.substr(0, queryPos);
        result.query = target.substr(queryPos + 1);
    } else {
        result.path = target;
    }

    // ✅ 2️⃣ 파일명 및 확장자 추출
    size_t lastSlash = result.path.find_last_of("/");
    if (lastSlash != std::string::npos) {
        result.filename = result.path.substr(lastSlash + 1);
    }

    size_t dotPos = result.filename.find_last_of(".");
    if (dotPos != std::string::npos) {
        result.extension = result.filename.substr(dotPos);
    }

    return result;
}