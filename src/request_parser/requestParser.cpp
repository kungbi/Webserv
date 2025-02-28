#include "requestParser.hpp"
#include "Request.hpp"

void RequestParser::parseRequestHeader(Request *request)
{
    if (!request) {
        std::cerr << "Error: request object is null" << std::endl;
        return;
    }

    // const std::string& originalRequest = request->getOriginalRequest();
    const std::string& originalRequest = "PATCH /api/resource/1 HTTP/1.1\n"
                                        "Host: api.example.com\n"
                                        "Content-Type: application/json\n"
                                        "Content-Length: 25\n";
    if (originalRequest.empty()) {
        std::cerr << "Error: originalRequest is empty!" << std::endl;
        return;
    }

    std::istringstream stream(originalRequest);
    std::string line;

    // 1️⃣ 첫 번째 줄 (요청 라인) 파싱
    if (!std::getline(stream, line)) {
        std::cerr << "Error: Could not read first line" << std::endl;
        return;
    }

    // \r\n 처리
    if (!line.empty() && line.back() == '\r') {
        line.pop_back();
    }

    std::istringstream lineStream(line);
    std::string method, target, version;
    
    // 모든 요소가 제대로 파싱되었는지 확인
    if (!(lineStream >> method >> target >> version)) {
        std::cerr << "Error: Invalid request line format" << std::endl;
        return;
    }

    try {
        request->setRequestType(method);
        request->setProtocolVersion(version);

        UriComponents uri = RequestParser::parseUri(target);
        request->setTarget(target);
        request->setPath(uri.path);
        request->setQuery(uri.query);
        request->setFilename(uri.filename);
        request->setExtension(uri.extension);
    } catch (const std::exception& e) {
        std::cerr << "Error parsing request line: " << e.what() << std::endl;
        return;
    }

    // 2️⃣ 헤더 파싱
    std::string currentHeader;  // 멀티라인 헤더를 위한 변수
    
    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        // 빈 줄이면 헤더 섹션 종료
        if (line.empty()) {
            break;
        }

        // 헤더 라인이 공백으로 시작하면 이전 헤더의 연속
        if (line[0] == ' ' || line[0] == '\t') {
            currentHeader += ' ' + line.substr(1);
            continue;
        }

        // 이전 헤더 처리
        if (!currentHeader.empty()) {
            processHeader(request, currentHeader);
        }
        currentHeader = line;
    }

    // 마지막 헤더 처리
    if (!currentHeader.empty()) {
        processHeader(request, currentHeader);
    }

    request->test();
}

// 새로운 헤더 처리 함수
void RequestParser::processHeader(Request* request, const std::string& header) {
    size_t colonPos = header.find(':');
    if (colonPos == std::string::npos) {
        std::cerr << "Warning: Invalid header format: " << header << std::endl;
        return;
    }

    std::string key = header.substr(0, colonPos);
    std::string value = header.substr(colonPos + 1);
    
    // 앞뒤 공백 제거
    while (!value.empty() && (value[0] == ' ' || value[0] == '\t')) {
        value = value.substr(1);
    }

    try {
        if (key == "Host") {
            size_t portPos = value.find(':');
            if (portPos != std::string::npos) {
                request->setHost(value.substr(0, portPos));
                request->setPort(std::stoi(value.substr(portPos + 1)));
            } else {
                request->setHost(value);
            }
        } else if (key == "Connection") {
            request->setConnection(value);
        } else if (key == "Content-Length") {
            request->setContentLength(std::stoi(value));
        } else if (key == "Accept") {
            request->setAccept(value);
        }
    } catch (const std::exception& e) {
        std::cerr << "Error processing header '" << key << "': " << e.what() << std::endl;
    }
}

UriComponents RequestParser::parseUri(const std::string& target) {
    UriComponents result;

    // ✅ 1️⃣ 쿼리 문자열 분리
    size_t queryPos = target.find("?");
    if (queryPos != std::string::npos) {
        result.path = target.substr(0, queryPos);  // 쿼리 문자열 제외한 경로
        result.query = target.substr(queryPos + 1); // `?` 이후 문자열을 쿼리로 저장
    } else {
        result.path = target;
    }

    // ✅ 2️⃣ 파일명 및 경로 추출
    size_t lastSlash = result.path.find_last_of("/");
    if (lastSlash != std::string::npos) {
        std::string lastSegment = result.path.substr(lastSlash + 1);  // `/` 뒤의 문자열
        size_t dotPos = lastSegment.find_last_of(".");

        if (dotPos != std::string::npos) {
            // ✅ 파일명과 확장자가 있는 경우 → 마지막 `/` 전까지가 경로
            result.filename = lastSegment;
            result.extension = lastSegment.substr(dotPos);
            result.path = result.path.substr(0, lastSlash);  // 파일명을 제외한 경로 저장
        } else {
            // ✅ 파일명이 아닌 경우 (예: `/api/resource/1`)
            result.filename = "";  // 파일명이 없으므로 빈 문자열
            result.path = target;  // 전체를 경로로 유지
        }
    }

    return result;
}
