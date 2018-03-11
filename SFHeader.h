#ifndef SFHeader_h
#define SFHeader_h
#include <string>
#include <vector>
#include "SFile.h"
#include <fstream>
#include <string>
#include <ctime>
#include "Block.h"
class SFHeader {
private:
	block_i blocks[maxFileNumber];
public:
	SFHeader();
	~SFHeader();
	std::vector<int> assignChunks(int chunkNum);
	std::vector<int> addFileHeader(block_i& block, std::fstream& archive);
	std::vector<int> getFile(std::string aname); // return the chunk number for this file.
	int getFileSize(std::string aname);
	bool delFileHeader(std::string filename, std::fstream& archive);
	std::vector<int> getFile(int atype, std::string aname); // return the chunk number for this file.
	std::vector<std::string> getFileName();
	void writeHeader(std::fstream& archive);
	void readHeader(std::fstream& archive);
	void update(std::fstream& archive, std::fstream& newarchive, SFHeader& other);
	void listFiles(std::string s);
	void listFiles();
  	void printHeader();
	int typeI2S(std::string fileName);
	std::string typeS2I(int atype);

	std::vector<std::string> find_txt_Files();

        block_i& getBlock(int i);
};

#endif
