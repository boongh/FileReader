#pragma once

#include "FileWriter.h"
#include "FileFormats.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <complex>
#include <unordered_map>


namespace FileWriter {

	void WriteCSV(const std::string& filename, std::unordered_map<std::string, std::string>& csvMap)
	{
		try {
			std::ofstream file(filename);
			if (!file) {
				throw std::exception("Failed to open file to write");
			}

			for (const auto& pair : csvMap) {
				file << pair.first << "," << pair.second << "\n";
			}

			file.close();
		}
		catch (const std::exception& e) {
			std::cout << "Unable to write file: " << e.what() << "\n";
		}
	}
}