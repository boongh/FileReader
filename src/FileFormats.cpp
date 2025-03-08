#include "FileFormats.h"
#include <iostream>

#pragma region WAV


//How to compare the headers
bool WAVHeader::operator == (const WAVHeader& b) const {
	return memcmp(this, &b, 44) == 0;
}


//Debugging for printing out the entire header data
void WAVHeader::PrintHeaderData() {
	using namespace std;
	//Check header
	cout << "Header" << endl;
	cout << "ChunkID: " << string(chunkID, 4) << endl;
	cout << "Chunk Size: " << chunkSize << endl;
	cout << "Format: " << string(format, 4) << endl;
	cout << "Subchunk1 ID: " << std::string(subchunk1ID, 4) << endl;
	cout << "Subchunk1 Size: " << subchunk1Size << endl;
	cout << "Audio Format: " << audioFormat << endl;
	cout << "Number of Channels: " << numChannels << endl;
	cout << "Sample Rate: " << sampleRate << endl;
	cout << "Byte Rate: " << byteRate << endl;
	cout << "Block Align: " << blockAlign << endl;
	cout << "Bits Per Sample: " << bitsPerSample << endl;
	cout << "Subchunk2 ID: " << string(subchunk2ID, 4) << endl;
	cout << "Subchunk2 Size: " << subchunk2Size << endl;
	cout << "End of header" << endl;

}

//How to compare the files
bool WAVFormat::operator == (const WAVFormat& b) const {
	return header == b.header && data == b.data;
}

bool WAVFormat::operator != (const WAVFormat& b) const {
	return !(*this == b);
}

//Regenerate the header of WAV file from the data
void WAVFormat::GenerateHeader(int samplerate, int numChannel) {
	memcpy(header.chunkID, "RIFF", 4);
	header.chunkSize = 36 + data.size() * sizeof(uint16_t);
	memcpy(header.format, "WAVE", 4);
	memcpy(header.subchunk1ID, "fmt ", 4);
	header.subchunk1Size = 16;
	header.audioFormat = 1;
	header.numChannels = numChannel;
	header.sampleRate = samplerate;
	header.byteRate = samplerate * sizeof(uint16_t) * numChannel;
	header.blockAlign = 2;
	header.bitsPerSample = 16;
	memcpy(header.subchunk2ID, "data", 4);
	header.subchunk2Size = data.size() * sizeof(uint16_t);
}

WAVFormat::WAVFormat() {
	GenerateHeader(0, 1);
}

WAVFormat::WAVFormat(std::vector<uint16_t> d) {
	data = d;
	GenerateHeader(0, 1);
}

#pragma endregion