#ifndef SFHeader_h
#define SFHeader_h
#include <string>
#include <vector>
#include "SFile.h"
class SFHeader {
private:
	std::vector<SFile> files;
public:
	SFHeader();
	SFHeader(const char*);
	~SFHeader();
	std::string encode();
	void decode();
};

#endif
