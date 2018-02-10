#include "stdafx.h"

#include "SliceHeaderParser.h"
#include <iostream>
#include <fstream>


SliceHeaderParser::SliceHeaderParser(const std::string &file) : _file (file) {

}


SliceHeaderParser::~SliceHeaderParser() {

}

int SliceHeaderParser::isNalStart(const char * buf, int size) {		
	switch (size) {
		case 4: {
			if (buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x00 && buf[3] == 0x01) {
				return 4;
			}
			break;
		}
		case 3: {
			if (buf[0] == 0x00 && buf[1] == 0x00 && buf[2] == 0x01) {
				return 3;
			}
			break;
		}
		case 2: {
			if (buf[0] == 0x00 && buf[1] == 0x00) {
				return 2;
			}
		}
		case 1: {
			if (buf[0] == 0x00) {
				return 1;
			}
			break;
		}
	}
	return -1;
}

void SliceHeaderParser::processBuffer(const char * buf, int size) {	
	int bytesLeft = size;
	int offset = 0;
	while (bytesLeft) {
		int nalSize = isNalStart(buf + offset, bytesLeft > 4 ? 4 : bytesLeft);
		offset++;
		bytesLeft--;
		if (nalSize == 3 || nalSize == 4) {
			int forbiddenZeroBit = 0;
			int nalRefIdc = 0;
			int nalUnitType = 0;

			char firstByte = buf[offset + nalSize];
			forbiddenZeroBit = (firstByte & 0x80) >> 7;
			nalRefIdc = (firstByte & 0x70) >> 4;
			nalUnitType = (firstByte & 0x1f);
			printf("offset: %d forbiddenZeroBit: %d nalRefIdc: %d nalUnitType %d \n", offset, forbiddenZeroBit, nalRefIdc, nalUnitType);
		}
	}
}

void SliceHeaderParser::parse() {
	const int bufferSize = 100;
	std::ifstream fileStream("video.mp4", std::ios::in | std::ios::binary);
	if (!fileStream.is_open()) {
		return;
	}
	char buffer [bufferSize];
	while (!fileStream.read(buffer, bufferSize).eof()) {		
		processBuffer(buffer, bufferSize);
	} 
}

void SliceHeaderParser::log(const std::string &msg) {
	std::cout << msg << std::endl;
}