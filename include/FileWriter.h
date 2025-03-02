#pragma once

#ifndef FILE_WRITER
#define FILE_WRITER

#include "FileFormats.h"
#include <string>




namespace FileWriter
{
	WAVFormat WriteWAV(const std::string& filename, const WAVFormat& wav);
}

#endif // !FILE_WRITER