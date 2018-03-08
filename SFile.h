#ifndef SFile_h
#define SFile_h
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include "Block.h"
class SFHeader;

class SFile { // encode and decode single file in header.
public:
	SFile();
	~SFile();
	static void writeArchive(std::ofstream& archive, std::vector<int> chunks, std::ifstream& file);
	static void readArchive(std::ifstream& archive, std::vector<int> chunks, std::ofstream& file, int size);
	static void writeWholeArchive(std::fstream& oldArchive, std::ofstream& newArchivestd::vector<block_i> oldBlocks, std::vector<block_i> newBlocks, std::unordered_map<int,int> newOldBlockMap);
};

#endif
