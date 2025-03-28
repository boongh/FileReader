#pragma once

#include "FileFormats.h"
#include "FileReader.h"
#include <vector>
#include <complex>
#include <fstream>
#include <iostream>


namespace FileReader {

    bool ReadPPM(const std::string& filename, PPMFormat& ppm) {

        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Failed to open file\n";
            return false;
        }

        // Read magic number (P3 or P6)
        file >> ppm.magic;
        if (ppm.magic != "P6" && ppm.magic != "P3") {
            std::cerr << "Unsupported PPM format\n";
            return false;
        }

        // Function to skip comments
        auto skipComments = [&file]() {
            while (file.peek() == '#' || std::isspace(file.peek())) {
                if (file.peek() == '#') {
                    std::string dummy;
                    std::getline(file, dummy);
                }
                else {
                    file.get();
                }
            }
            };

        // Read header values (width, height, maxval)
        skipComments();
        file >> ppm.width;
        skipComments();
        file >> ppm.height;
        skipComments();
        file >> ppm.maxval;
        file.get(); // consume the whitespace (usually newline) after maxval

        // Check for valid header values
        if (ppm.width <= 0 || ppm.height <= 0 || ppm.maxval <= 0) {
            std::cerr << "Invalid header values\n";
            return false;
        }

        // Allocate storage for pixel data.
        size_t dataSize = ppm.width * ppm.height * 3; // 3 bytes per pixel (RGB)
        ppm.data.resize(dataSize);

        if (ppm.magic == "P6") {
            // Read binary pixel data.
            file.read(reinterpret_cast<char*>(ppm.data.data()), dataSize);
            if (!file) {
                std::cerr << "Error reading pixel data\n";
                return false;
            }
        }
        else {
            // For P3 format, read pixel values as ASCII integers.
            for (size_t i = 0; i < dataSize; i++) {
                int pixel;
                file >> pixel;
                if (!file) {
                    std::cerr << "Error reading pixel value\n";
                    return false;
                }
                ppm.data[i] = static_cast<unsigned char>(pixel);
            }
        }
        return true;
    }
}