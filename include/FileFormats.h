#pragma once

#ifndef  FILE_FORMATS
#define FILE_FORMATS


#include <vector>
#include <string>

/// <summary>
/// For specifying the format of the file to be read
/// </summary>
enum Format{
	JPEG,
	WAV,
	MP3,
	MP4,
	AVI,
};


#pragma region Base

#pragma pack(push, 1) 
struct Header {

};
struct File {

};

class Pixel {

};

class PixelRGB : Pixel{
public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
};

class PixelRGBA : Pixel {
public:
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
};


#pragma pack(pop)

#pragma endregion

#pragma region WAVFormat

//WAV file format header
#pragma pack(push, 1) // Ensure no padding in WAVHeader
struct WAVHeader : Header {
    char chunkID[4];                // "RIFF"
    unsigned int chunkSize;         // File size - 8 bytes
    char format[4];                 // "WAVE"
    char subchunk1ID[4];            // "fmt "
    unsigned int subchunk1Size;     // Size of fmt chunk
    unsigned short audioFormat;     // Audio format (1 for PCM)
    unsigned short numChannels;     // Number of channels
    unsigned int sampleRate;        // Sample rate
    unsigned int byteRate;          // Byte rate
    unsigned short blockAlign;      // Block align
    unsigned short bitsPerSample;   // Bits per sample
    char subchunk2ID[4];            // "data"
    unsigned int subchunk2Size;              // Size of data chunk

    bool operator == (const WAVHeader& b) const;

    void PrintHeaderData();
};
#pragma pack(pop)


#pragma pack(push, 1)
struct WAVFormat : File {


    //Header
    WAVHeader header;

    //Actual audio data
    std::vector<int16_t> data;		//Actual audio data

    WAVFormat(std::vector<int16_t>);

	//Blank constructor
    WAVFormat();

    //Operator overloading
	bool operator == (const WAVFormat& b) const;
    bool operator != (const WAVFormat& b) const;

    void GenerateHeader(int samplerate, int numberChannel);
};
#pragma pack(pop)


#pragma endregion


#pragma region PPMFormat


struct PPMFormat {
    std::string magic;
    int width;
    int height;
    int maxval;
    std::vector<unsigned char> data;
};


#pragma endregion


#pragma region QOIFormat

#pragma pack(push, 1)
struct QOIHeader {
    char magic[4];

    uint32_t width;
	uint32_t height;

	uint8_t channels;
	uint8_t colorSpace;
};


class QOIData {};


struct QOI_RGB :QOIData {
    const char tag = 0b11111110;

public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

struct QOI_RGBA :QOIData {
    const char tag = 0b11111111;

public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
};

struct QOI_INDEX : QOIData {    
    //Stored as 2 bits for tag and 6 bits for index
    char tagindex;

public:
	void SetIndex(uint8_t index) {
		tagindex = 0b11000000 | index;
	}

	uint8_t GetIndex() {
		return tagindex & 0b00111111;
	}
};


struct QOI_DIFF : QOIData {
    constexpr static uint8_t QOI_DIFF_TAG = 0b01000000;
    constexpr static uint8_t MASK_R = 0b00110000;
    constexpr static uint8_t MASK_G = 0b00001100;
    constexpr static uint8_t MASK_B = 0b00000011;

    char tagdiff;
public:
    void SetDiff_R(uint8_t diff) {
        tagdiff = QOI_DIFF_TAG | MASK_R & (diff << 4);
    }

	uint16_t GetDiff_R() {
		return (tagdiff & 0b00110000) >> 4;
	}

    void SetDiff_G(uint8_t diff) {
        tagdiff = QOI_DIFF_TAG | MASK_G & (diff << 2);
    }

	uint8_t GetDiff_G() {
		return (tagdiff & 0b00001100) >> 2;
	}

    void SetDiff_B(uint8_t diff) {
        tagdiff = QOI_DIFF_TAG | MASK_B & (diff);
    }

    uint8_t GetDiff_B() {
		return tagdiff & 0b00000011;
    }

    uint8_t GetDiff_All() {
        return tagdiff & 0b01111111;
    };
};

struct QOI_LUMA : QOIData {
    constexpr static uint8_t QOI_LUMA_TAG = 0b10000000;
    constexpr static uint8_t MASK_LUMA_G = 0b001111111;
	constexpr static char UpperMask = 0b11110000;
	constexpr static char LowerMask = 0b00001111;
    char tagluma_g;
    char dr_db;

public:
    void SetLuma_G(uint8_t g) {
		tagluma_g = QOI_LUMA_TAG | MASK_LUMA_G & g;
    }

	uint8_t GetLuma_G() {
		return tagluma_g & MASK_LUMA_G;
	};

    void SetLuma_R(uint8_t r) {
        dr_db = (r << 4) | (LowerMask & dr_db);
    }

	uint8_t GetLuma_R() {
		return (dr_db & 0b11110000) >> 4;
	}

	void SetLuma_B(uint8_t b) {
		dr_db = b | (UpperMask & dr_db);
	}

	uint8_t GetLuma_B() {
		return dr_db & 0b00001111;
	}
};


struct QOI_RUN : QOIData {
    constexpr static uint8_t QOI_RUN_TAG = 0b11000000;
    constexpr static uint8_t MASK_RUN = 0b00111111;
    char tagrun;
public:
    void SetRun(uint8_t run) {
        tagrun = QOI_RUN_TAG | (MASK_RUN & run);
    }
    uint8_t GetRun() {
        return tagrun & 0b00111111;
    };
};

struct QOIFormat : File {
	QOIHeader header;
	std::vector<char> data;
};


#pragma pack(pop)

#pragma endregion

#endif // ! FILE_FORMATS