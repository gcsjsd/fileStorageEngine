#ifndef SFile_cpp
#define SFile_cpp
#include "SFile.h"
#include "SFHeader.h"
SFile::SFile() {

}

SFile::SFile(std::string) {

}

SFile::SFile(std::string atype, std::string aname, int asize) {
  this->type = atype;
  this->name = aname;
  this->size = asize;
  this->numChunks = asize / 1024;
  if (asize % 1024 != 0) {
    numChunks += 1;
  }
}

SFile::~SFile() {

}

char* SFile::readChunk(std::ifstream &file, int chunk) {

}

void SFile::writeChunk(std::ofstream &filem, int chunk) {

}
std::string SFile::encode() {

}

std::string SFile::decode(const char* header) {

}


#endif

