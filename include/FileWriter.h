#pragma once
#include "FileHeaders.h"
#include <string>

namespace FileWriter
{
	void writeWAV(const std::string& filename, const WAVFormat& wav);
}