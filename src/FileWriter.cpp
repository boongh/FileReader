#include "FileWriter.h"
#include "FileReader.h"
#include "FileFormats.h"
#include <fstream>
#include <iostream>

namespace FileWriter {
	/// <summary>
	/// Write Wav file format
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="wav"></param>
	WAVFormat WriteWAV(const std::string& filename, const WAVFormat& wav) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file) {
				throw std::exception("Failed to open file");
			}

			
			//Write the header
			file.write(reinterpret_cast<const char*>(&wav.header), sizeof(WAVHeader));	

			file.write(reinterpret_cast<const char*>(wav.data.data()), wav.data.size() * sizeof(int16_t));
			file.close();

			return FileReader::ReadWAV(filename);
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file" << e.what() << "\n";
		}
	}
}

