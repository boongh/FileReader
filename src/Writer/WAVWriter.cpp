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
    bool WriteWAV(const std::string& filename, const WAVFormat& bufferWrite) {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            return false;
        }

        /*std::cout << filename << " : writing\n";
        std::cout << "Datapoint : " << bufferWrite.data.size() << "\n";
        std::cout << "Size of a point : " << sizeof(bufferWrite.data[0]) << "\n";
        std::cout << "Sample rate : " << bufferWrite.header.sampleRate << "\n";
        std::cout << "Channels : " << bufferWrite.header.numChannels << "\n";*/

        // Write the header
        if (!file.write(reinterpret_cast<const char*>(&bufferWrite.header), sizeof(WAVHeader))) {
            std::cerr << "Failed to write file header" << "\n";
            return false;
        }

        // Write the data
        if (!file.write(reinterpret_cast<const char*>(bufferWrite.data.data()), bufferWrite.data.size() * sizeof(int16_t))) {
            std::cerr << "Failed to write file data" << "\n";
            return false;
        }

        file.close();

        return true;
    }
}
