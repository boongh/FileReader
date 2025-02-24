#include "FileHeaders.h"
#include "FileReader.h"
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>


#ifndef FILE_READER
#define FILE_READER


using namespace std;
namespace FileReader {

	/// <summary>
	/// Read Wav file format
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	WAVFormat readWAV(const char* filename) {
		try {
			WAVFormat wav;
			std::ifstream file(filename, std::ios::binary | std::ios::ate);

			if (!file) {
				cerr << "Failed to open file\n";
				return wav;
			}

			streamoff bufferSize = file.tellg();

			if (bufferSize < 0) {
				cerr << "Error determining file size.\n";
				return wav;
			}

			file.seekg(0, std::ios::beg);

			wav.data.resize(static_cast<size_t>(bufferSize - sizeof(WAVFormat)));

			if (!file.read(reinterpret_cast<char*>(wav.data.data()), bufferSize)) {
				cerr << "Error reading the file." << std::endl;
				return wav;

			}

			file.close();
			return wav;
		}
		catch (const std::exception&) {
			std::cout << "Unable to read file";
		}
	}

}

#endif // !FILE_READER