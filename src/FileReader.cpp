#include "FileFormats.h"
#include "FileReader.h"
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>

using namespace std;
namespace FileReader {

	/// <summary>
	/// Read Wav file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	WAVFormat ReadWAV(const std::string& filename) {
		try {
			//Parse file into WAVFormat struct
			WAVFormat wav;
			std::ifstream file(filename, std::ios::binary | std::ios::ate);

			if (!file) {
				cerr << "Failed to open file\n";
				return wav;
			}

			//Size of the file
			streamoff bufferSize = file.tellg();

			if (bufferSize < 0) {
				cerr << "Error determining file size.\n";
				return wav;
			}


			//Ensure reader head is at the start
			file.seekg(0, std::ios::beg);


			//Read the header
			file.read(reinterpret_cast<char*>(&wav.header), sizeof(WAVHeader));


			//Number of samples = filesize - size of header after chunksize(44 - 8) / size of sample (2 bytes)
			wav.data.resize((wav.header.chunkSize - 36) >> 1);

			//Read data into header
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