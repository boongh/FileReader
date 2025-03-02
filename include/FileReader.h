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
	WAVFormat ReadWAV(const std::string& filename);
}

#endif // !FILE_READER