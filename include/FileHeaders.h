#pragma once
#include <vector>


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

#pragma pack(push, 1) 
struct Header {

};
#pragma pack(pop)


#pragma pack(push, 1) // Ensure no padding in WAVHeader
struct WAVHeader {
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
    unsigned int subchunk2Size;     // Size of data chunk

    bool operator == (const WAVHeader& b) const {
        return memcmp(chunkID, b.chunkID, 4) == 0 &&
            chunkSize == b.chunkSize &&
            memcmp(format, b.format, 4) == 0 &&
            memcmp(subchunk1ID, b.subchunk1ID, 4) == 0 &&
            subchunk1Size == b.subchunk1Size &&
            audioFormat == b.audioFormat &&
            numChannels == b.numChannels &&
            sampleRate == b.sampleRate &&
            byteRate == b.byteRate &&
            blockAlign == b.blockAlign &&
            bitsPerSample == b.bitsPerSample &&
            memcmp(subchunk2ID, b.subchunk2ID, 4) == 0 &&
            subchunk2Size == b.subchunk2Size;
    }
};
#pragma pack(pop)

using namespace std;

struct File {

};

struct WAVFormat : File {
	//Header
	WAVHeader header;

	//Actual audio data
	vector<int16_t> data;		//Actual audio data

	//Operator overloading
	bool operator == (WAVFormat b)
	{
		if (header == b.header && data == b.data)
		{
			return true;
		}
		return false;
	}
};

