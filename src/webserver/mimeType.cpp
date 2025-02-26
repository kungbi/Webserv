#include "mimeTypes.hpp"

#include <iostream>
#include <map>

// MIME 타입 목록 정의
std::map<std::string, std::string> mimeTypes = {
	// 텍스트 파일
	{".html", "text/html"},
	{".htm", "text/html"},
	{".css", "text/css"},
	{".js", "application/javascript"},
	{".json", "application/json"},
	{".xml", "application/xml"},
	{".csv", "text/csv"},
	{".txt", "text/plain"},

	// 이미지 파일
	{".png", "image/png"},
	{".jpg", "image/jpeg"},
	{".jpeg", "image/jpeg"},
	{".gif", "image/gif"},
	{".bmp", "image/bmp"},
	{".ico", "image/vnd.microsoft.icon"},
	{".svg", "image/svg+xml"},
	{".webp", "image/webp"},
	{".tif", "image/tiff"},
	{".tiff", "image/tiff"},

	// 오디오 파일
	{".mp3", "audio/mpeg"},
	{".wav", "audio/wav"},
	{".ogg", "audio/ogg"},
	{".m4a", "audio/mp4"},
	{".aac", "audio/aac"},

	// 비디오 파일
	{".mp4", "video/mp4"},
	{".mpeg", "video/mpeg"},
	{".mpg", "video/mpeg"},
	{".avi", "video/x-msvideo"},
	{".mov", "video/quicktime"},
	{".wmv", "video/x-ms-wmv"},
	{".flv", "video/x-flv"},
	{".webm", "video/webm"},

	// 문서 파일
	{".pdf", "application/pdf"},
	{".doc", "application/msword"},
	{".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
	{".xls", "application/vnd.ms-excel"},
	{".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
	{".ppt", "application/vnd.ms-powerpoint"},
	{".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"},
	{".odt", "application/vnd.oasis.opendocument.text"},
	{".ods", "application/vnd.oasis.opendocument.spreadsheet"},
	{".odp", "application/vnd.oasis.opendocument.presentation"},

	// 압축 파일
	{".zip", "application/zip"},
	{".rar", "application/x-rar-compressed"},
	{".tar", "application/x-tar"},
	{".gz", "application/gzip"},
	{".7z", "application/x-7z-compressed"},

	// 기타 실행 파일 및 바이너리
	{".exe", "application/octet-stream"},
	{".bin", "application/octet-stream"},
	{".dll", "application/octet-stream"},
	{".iso", "application/x-iso9660-image"},
	{".img", "application/octet-stream"},

	// 글꼴 파일
	{".woff", "font/woff"},
	{".woff2", "font/woff2"},
	{".ttf", "font/ttf"},
	{".otf", "font/otf"},

	// 기타
	{".wasm", "application/wasm"},
	{".rtf", "application/rtf"}
};

std::string getContentType(const std::string& fileExtension) {
	if (mimeTypes.find(fileExtension) != mimeTypes.end()) {
		return mimeTypes[fileExtension];
	}
	return "application/octet-stream";  // 기본값 (알 수 없는 파일)
}
