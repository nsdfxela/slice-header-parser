#include "stdafx.h"

#include "SliceHeaderParser.h"


SliceHeaderParser::SliceHeaderParser(const std::string &file) : _file (file), _fileStream(file, std::ios::in | std::ios::binary) {

}

SliceHeaderParser::~SliceHeaderParser() {

}

bool SliceHeaderParser::parseMdat() {
	if (_queue.size() != 4)
		return false;
	if (_queue[3] == 'm' && _queue[2] == 'd' && _queue[1] == 'a' && _queue[0] == 't') {
		return true;
	}
	return false;
	
}

void SliceHeaderParser::parse() {
	std::istream_iterator<char> begin(_fileStream), end;
	std::istream_iterator<char> pos;
	int byteOffset = 0;
	for (pos = begin; pos != end; pos++) {
		if (_queue.size() == 4) {
			_queue.pop_back();
		}
		_queue.push_front(*pos);
		byteOffset++;
		if (parseMdat()) {
			printf("Mdat");
		}
	}

}

void SliceHeaderParser::log(const std::string &msg) {
	std::cout << msg << std::endl;
}