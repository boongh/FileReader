#pragma once

#ifndef  FILE_FORMATS
#define FILE_FORMATS


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


#pragma region Base

#pragma pack(push, 1) 
struct Header {

};
struct File {

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

#endif // ! FILE_FORMATS