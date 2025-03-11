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
            
            std::cout << filename << " : writing\n";
            std::cout << "Datapoint : " << bufferWrite.data.size() << "\n";
            std::cout << "Size of a point : " << sizeof(bufferWrite.data[0]) << "\n";
            std::cout << "Sample rate : " << bufferWrite.header.sampleRate << "\n";
            std::cout << "Channels : " << bufferWrite.header.numChannels << "\n";
            
            // Write the header
            if (!file.write(reinterpret_cast<const char*>(&bufferWrite.header), sizeof(WAVHeader))) {
                std::cerr << "Failed to write file header" << "\n";
            }

            // Write the data
            if (!file.write(reinterpret_cast<const char*>(bufferWrite.data.data()), bufferWrite.data.size() * sizeof(int16_t))) {
                std::cerr << "Failed to write file data" << "\n";
            }

            file.close();

            return FileReader::ReadWAV(filename);
        }
        catch (const std::exception& e) {
            std::cout << "Unable to write file: " << e.what() << "\n";
        }
    }


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
	void WriteText(const std::string& filename, std::vector<double>& write)
	{
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

	void WriteText(const std::string& filename, const std::vector<std::complex<double>>& write, bool writeMagnitude)
	{
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
}	
