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
#include <cstdio>

namespace FileWriter
{
	bool WriteWAV(const std::string& filename, const WAVFormat& bufferWrite);

	template <typename T1, typename T2>
	void WriteCSV(const std::string& filename, std::unordered_map<T1, T2> csvMap) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}

			for (std::pair<T1, T2> pair : csvMap) {
				file << pair.first << ", " << pair.second << "\n";
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}

	template <typename T>
	void WriteText(const std::string& filename, std::vector<T>& write) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}
			for (int i = 0; i < write.size(); i++) {
				file << write[i] << "\n";
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}


	template <typename T>
	void WriteText(const std::string& filename, const std::vector<std::complex<T>>& write, bool writeMagnitude) {
		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}

			if (!writeMagnitude) {
				for (int i = 0; i < write.size(); i++) {
					file << write[i] << "\n";
				}
			}
			else {
				for (int i = 0; i < write.size(); i++) {
					file << abs(write[i]) << "\n";
				}
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}

	template <typename T>
	void FastWriteText(const std::string& filename, std::vector<T>& write) {

		std::vector<char> writeBuffer;
		writeBuffer.reserve(30 * write.size());

		char lineBuffer[128];

		for (const T& word : write) {
			//Format magnitude
			int len = std::snprintf(lineBuffer, sizeof(lineBuffer), "%s\n", std::to_string(word));

			//Append into write buffer
			writeBuffer.insert(writeBuffer.end(), lineBuffer, lineBuffer + len);
		}

		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}

			file.write(writeBuffer.data(), writeBuffer.size());
			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}


	/// <summary>
	/// Write running data as text support file type complex number
	/// </summary>
	/// <param name="filename"></param>
	/// <param name="write"></param>
	template <typename ComType>
	void FastWriteText(const std::string& filename, const std::vector<std::complex<ComType>>& write, bool WriteMagnitude) {

		std::vector<char> writeBuffer;
		writeBuffer.reserve(30 * write.size());

		char lineBuffer[128];

		if (WriteMagnitude) {
			for (const std::complex<ComType>& word : write) {
				//Format magnitude
				int len = std::snprintf(lineBuffer, sizeof(lineBuffer), "%f\n", std::abs(word));

				//Append into write buffer
				writeBuffer.insert(writeBuffer.end(), lineBuffer, lineBuffer + len);
			}
		}
		else {
			for (std::complex<ComType> word : write) {
				//Format real+imag
				int len = std::snprintf(lineBuffer, sizeof(lineBuffer), "%f+%f\n", word.real(), word.imag());

				//Append into write buffer
				writeBuffer.insert(writeBuffer.end(), lineBuffer, lineBuffer + len);
			}
		}

		try {
			std::ofstream file(filename, std::ios::binary);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open file to write");
			}

			file.write(writeBuffer.data(), writeBuffer.size());
			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}

}
#endif // !FILE_WRITER