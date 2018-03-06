#ifndef SFile_h
#define SFile_h
#include <string>
#include <fstream>
class SFHeader;

class SFile { // encode and decode single file in header.
private:
	std::string type;
	std::string name;
	int size;
	int numChunks;
	vector<int> chunks;
public:
	SFile();
	SFile(std::string);
	SFile(std::string atype, std::string aname, int asize);
	~SFile();
	char* readChunk(std::ifstream& file, int chunk);
	void writeChunk(std::ofstream& archive, int chunk, char* buffer);
	void writeArchive(std::ofstream archive, vector<int> chunks, char* buffer);
	void readArchive(std::ifstream archive, vector<int> chunks, char* buffer);
	std::string encode();
	static std::string decode(const char* header);
};

#endif
