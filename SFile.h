#ifndef SFile_h
#define SFile_h
#include <string>
#include <fstream>
class SFile { // encode and decode single file in header
private:


public:
	SFile();
	SFile(std::string);
	~SFile();
	char* readContent(std::ifstream& file);
	void writeContent(std::ofstream& file);
	std::string encode();
	static std::string decode(const char* header);
};

#endif
