#include "stdafx.h"

#include "SliceHeaderParser.h"


SliceHeaderParser::SliceHeaderParser(const std::string &file) : _file (file), 
_fileStream(file, std::ios::in | std::ios::binary), 
begin(_fileStream) {

}

SliceHeaderParser::~SliceHeaderParser() {

}

bool SliceHeaderParser::parseMdat() {
	if (_queue.size() != 4)
		return false;
	if (   _queue[3] == 'm' 
		&& _queue[2] == 'd' 
		&& _queue[1] == 'a' 
		&& _queue[0] == 't') {
		return true;
	}
	return false;
	
}

void SliceHeaderParser::parseNalu(int &type) {
	unsigned char size[4];
	size[0] = *++pos;
	size[1] = *++pos;
	size[2] = *++pos;
	size[3] = *++pos;
	byteOffset += 4;
	int32_t l = int((unsigned char)(size[0]) << 24 |
					(unsigned char)(size[1]) << 16 |
					(unsigned char)(size[2]) << 8 |
					(unsigned char)(size[3]));

	int forbiddenZeroBit = 0;
	int nalRefIdc = 0;
	int nalUnitType = 0;

	
	unsigned char firstByte = *++pos;
	byteOffset++;
	forbiddenZeroBit = (firstByte & 0x80) >> 7;
	nalRefIdc = (firstByte & 0x70) >> 4;
	nalUnitType = (firstByte & 0x1f);
	type = nalUnitType;
	
	for (int i = 0; i < l - 1; i++) {
		pos++;
		byteOffset++;
	}
}

void SliceHeaderParser::parse() {	
	
	for (pos = begin; pos != end; pos++) {
		byteOffset++;
		if (_queue.size() == 4) {
			_queue.pop_back();
		}
		_queue.push_front(*pos);
		
		if (parseMdat()) {
			printf("Mdat");
			break;
		}
	}

	int type = 0;
	parseNalu(type);
	parseNalu(type);
	parseNalu(type);
}

void SliceHeaderParser::log(const std::string &msg) {
	std::cout << msg << std::endl;
}