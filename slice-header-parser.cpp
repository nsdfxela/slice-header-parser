// slice-header-parser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SliceHeaderParser.h"

int main()
{
	SliceHeaderParser parser("video.mp4");
	parser.parse();

    return 0;
}

