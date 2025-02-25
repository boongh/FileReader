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
	WAVFormat readWAV(const std::string& filename) {
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


			//Read the header
			file.read(reinterpret_cast<char*>(&wav.header), sizeof(WAVHeader));

			size_t numSamples = (bufferSize  - sizeof(WAVHeader)) / sizeof(int16_t);
			wav.data.resize(numSamples);

			if (!file.read(reinterpret_cast<char*>(wav.data.data()), bufferSize - sizeof(WAVHeader))) {
				cerr << "Error reading the file : " << filename << std::endl;
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