#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <deque>
#pragma once
#define MAX_BUFFER_SIZE 1000
class SliceHeaderParser
{
public:
	SliceHeaderParser(const std::string &file);
	~SliceHeaderParser();
	void parse();
private:
	bool parseMdat();
	int _fileOffset = 0;
	int _bufferOffset = 0;
	
	std::ifstream _fileStream;
	
	std::string _file;
	std::deque <char> _queue;
	void log(const std::string &msg);
};

