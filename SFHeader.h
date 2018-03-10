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
	void delFileHeader(int atype, std::string aname, std::fstream& archive);
	std::vector<int> getFile(int atype, std::string aname); // return the chunk number for this file.
	int getFileSize(int atype, std::string aname);
	void writeHeader(std::fstream& archive);
	void readHeader(std::fstream& archive);
	void updateWholeHeader(std::fstream& archive);
	void listFiles(std::string s);
	void listFiles();
    void printHeader();
	int typeI2S(std::string type);
	std::string typeS2I(int atype);

	std::vector<std::string> find_txt_Files();
};

#endif
