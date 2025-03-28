#pragma once

#ifndef FILE_READER
#define FILE_READER



#include <string>
#include <vector>
#include <complex>
#include <FileFormats.h>
#include <string>

namespace FileReader {
	//static std::vector<unsigned char> readData(const char* filePath);
	bool ReadWAV(const std::string& filename, WAVFormat& out);

	bool ReadPPM(const std::string& filename, PPMFormat& out);

	bool ReadQOI(const std::string& filename, QOIFormat& out);
}

#endif // !FILE_READER