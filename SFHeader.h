#ifndef SFHeader_h
#define SFHeader_h
#include <string>
class SFHeader {
private:
	
public:
	SFHeader();
	~SFHeader();
	std::string encode();
	void decode();
}