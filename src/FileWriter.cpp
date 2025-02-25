#include "FileWriter.h"
#include "FileHeaders.h"
#include <fstream>
#include <iostream>


#ifndef FILE_WRITER
#define FILE_WRITER

namespace FileWriter {
	/// <summary>
	/// Write Wav file format
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="wav"></param>
	void writeWAV(const std::string& filename, const WAVFormat& wav) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file) {
				std::cerr << "Failed to open file\n";
				return;
			}

			
			//Write the header
			file.write(reinterpret_cast<const char*>(&wav.header), sizeof(WAVHeader));	

			file.write(reinterpret_cast<const char*>(wav.data.data()), wav.data.size() * sizeof(int16_t));
			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file" << e.what() << "\n";
		}
	}
}

#endif // !FILE_WRITER
