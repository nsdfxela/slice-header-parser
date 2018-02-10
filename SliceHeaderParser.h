#include <string>

#pragma once
class SliceHeaderParser
{
public:
	SliceHeaderParser(const std::string &file);
	~SliceHeaderParser();
	void parse();
private:
	void processBuffer(const char *buf, int size);
	std::string _file;
	void log(const std::string &msg);
	int isNalStart(const char * buf, int size);
};

