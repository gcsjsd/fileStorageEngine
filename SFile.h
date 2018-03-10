#ifndef SFile_h
#define SFile_h
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <unordered_map>
#include "Block.h"
class SFHeader;

class SFile {
public:
	SFile();
	~SFile();
	static void writeArchive(std::fstream& archive, std::vector<int> chunks, std::ifstream& file, int size);
	static void readArchive(std::fstream& archive, std::vector<int> chunks, std::ofstream& file, int size);
	static void writeWholeArchive(std::fstream& oldArchive, std::ofstream& newArchive, std::vector<block_i> oldBlocks, std::vector<block_i> newBlocks, std::unordered_map<int,int> newOldBlockMap);
};

#endif
