#pragma once

#include "FileFormats.h"
#include "FileReader.h"
#include <vector>
#include <complex>
#include <fstream>


namespace FileReader {
    bool ReadQOI(const std::string& filename, QOIFormat& out)
    {
		std::ifstream file(filename, std::ios::ate);


        return false;
    }

    static int hashcolor(uint32_t colour) {
		return 0;
    }
}