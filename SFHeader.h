#ifndef SFHeader_h
#define SFHeader_h
#include <string>
#include <vector>
#include "SFile.h"
#include <fstream>
#include "Block.h"
class SFHeader {
private:
	block_i blocks[maxFileNumber];
public:
	SFHeader();
	~SFHeader();
	std::vector<int> assignChunks(int chunkNum);
	std::vector<int> addFileHeader(block_i& block, std::ofstream archive);
	void delFileHeader(int atype, std::string aname, std::ofstream archive);
	std::vector<int> getFile(int atype, std::string aname); // return the chunk number for this file.
	int getFileSize(int atype, std::string aname);
	void writeHeader(std::ofstream& archive);
	void readHeader(std::ifstream& archive);
	void updateWholeHeader(std::fstream& archive);
	void listFiles(std::string s);
	void listFiles();

};

#endif
