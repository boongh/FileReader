#pragma once

#ifndef FILE_WRITER
#define FILE_WRITER

#include "FileFormats.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iostream> // Include this header for std::cout
#include <complex>

namespace FileWriter
{
	WAVFormat WriteWAV(const std::string& filename, const WAVFormat& bufferWrite);
	void WriteCSV(const std::string& filename, std::unordered_map<std::string, std::string> csvMap);

	void WriteText(const std::string& filename, std::vector<double> write);
	void WriteText(const std::string& filename, std::vector<std::complex<double>> write, bool writeMagnitude);
}

#endif // !FILE_WRITER