#pragma once
#include <vector>


/// <summary>
/// For specifying the format of the file to be read
/// </summary>
enum Format
{
	JPEG,
	WAV,
	MP3,
	MP4,
	AVI,
};

using namespace std;

struct File {

};
struct WAVFormat : File {
	//Header
	char chunkID[4];				//"RIFF"
	unsigned int chunkSize;			//Files size in bytes
	char format[4];					//"WAVE"
	char subchunk1ID[4];			//"fmt "
	unsigned int subchunk1Size;		//Size of the fmt chunk
	unsigned short audioFormat;		//Audio format (1 for PCM)
	unsigned short numChannels;		//Number of channels
	unsigned int sampleRate;		//Sample rate
	unsigned int byteRate;			//Byte rate
	unsigned short blockAlign;		//Block align
	unsigned short bitsPerSample;	//Bits per sample
	char subchunk2ID[4];			//"data" section begins here
	unsigned int subchunk2Size;		//Size of the data chunk

	//Actual audio data
	vector<int16_t> data;		//Actual audio data
};

