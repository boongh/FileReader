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
	WAVFormat WriteWAV(const std::string& filename, const WAVFormat& bufferWrite) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file) {
				throw std::exception("Failed to open file");
			}
			
			//Write the header
			if (!file.write(reinterpret_cast<const char*>(&bufferWrite.header), sizeof(WAVHeader))) {
				std::cerr << "Failt to write file header" << "\n";
			}

			//Write the data
			if (!file.write(reinterpret_cast<const char*>(bufferWrite.data.data()), bufferWrite.data.size()  / sizeof(uint16_t))) {
				std::cerr << "Failt to write file header" << "\n";
			}

			file.close();

			return FileReader::ReadWAV(filename);
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file" << e.what() << "\n";
		}
	}


	void WriteCSV(const std::string& filename, unordered_map<string, string> csvMap)
	{
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file) {
				throw std::exception("Failed to open file to write");
			}
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file" << e.what() << "\n";
		}
	}
	void WriteText(const std::string& filename, std::vector<double> write)
	{
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}
			for (int i = 0; i < write.size(); i++) {
				file << i << ", " << write[i] << "\n";
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}

	void WriteText(const std::string& filename, std::vector<std::complex<double>> write, bool writeMagnitude)
	{
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}

			if (!writeMagnitude) {
				for (int i = 0; i < write.size(); i++) {
					file << i << ", " << write[i] << "\n";
				}
			}
			else {
				for (int i = 0; i < write.size(); i++) {
					file << i << ", " << abs(write[i]) << "\n";
				}
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}
}

