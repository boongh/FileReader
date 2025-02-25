#pragma once

#include <string>
#include <vector>
#include <complex>
#include <FileHeaders.h>
#include <string>

namespace FileReader {
	//static std::vector<unsigned char> readData(const char* filePath);
	WAVFormat readWAV(const std::string& filename);
}
