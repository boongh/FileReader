#include "FileFormats.h"
#include "FileReader.h"
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>


namespace FileReader {

	/// <summary>
	/// Read Wav file
	/// </summary>
	/// <param name="filename"></param>
	/// <returns></returns>
	bool ReadWAV(const std::string& filename, WAVFormat& out) {
		try {

			//Parse file into WAVFormat struct
			std::ifstream file(filename, std::ios::binary | std::ios::ate);

			if (!file) {
				std::cerr << "Failed to open file\n";
				return false;
			}

			//Size of the file
			std::streamoff bufferSize = file.tellg();

			if (bufferSize < 0) {
				std::cerr << "Error determining file size.\n";
				return false;
			}


			//Ensure reader head is at the start
			file.seekg(0, std::ios::beg);

			//Read the header
			file.read(reinterpret_cast<char*>(&out.header), sizeof(WAVHeader));

			int Size = (bufferSize - sizeof(WAVHeader)) / sizeof(int16_t);
			if (Size % out.header.numChannels != 0) {
				//Pad wav files cuz sometimes it bugs and have weird number of samples, pad with silence
				Size += Size % out.header.numChannels;
			}

			//Number of samples = filesize  - header / size of sample (2 bytes)
			out.data.resize(Size);

			//Read data into header
			if (!file.read(reinterpret_cast<char*>(out.data.data()), bufferSize - sizeof(WAVHeader))) {
				std::cerr << "Error reading the file : " << filename << std::endl;
				return false;
			}

			file.close();
			return true;
		}
		catch (const std::exception&) {
			std::cout << "Unable to read file";
		}
	}

}