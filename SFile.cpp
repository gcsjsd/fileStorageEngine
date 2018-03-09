#ifndef SFile_cpp
#define SFile_cpp
#include "SFile.h"
#include "SFHeader.h"
#include <iostream>
SFile::SFile() {

}

SFile::~SFile() {

}

void SFile::writeArchive(std::fstream &archive, std::vector<int> chunks, std::ifstream &file, int size) {
  std::cout << "starting write archive " << std::endl;
  int remaining = size;
  int numChunks = chunks.size();
  file.seekg(0);
  for (int i = 0; i < numChunks; i++) {
    int cur_chunk = chunks[i];
    int writeSize = (i == numChunks-1) ? remaining : chunk_size;
    archive.seekp(header_size+cur_chunk*chunk_size);
    char* buffer = new char[writeSize];
    file.read(buffer, writeSize);
    archive.write(buffer, writeSize);
    delete[] buffer;
    std::cout << "write size: " << writeSize << std::endl;
    if (writeSize != chunk_size) {
    	int fillSize = chunk_size - writeSize;
      std::cout << fillSize << std::endl;
    	char* buffer2 = new char[fillSize];
      for (int k = 0; k < fillSize; k++) {
        buffer2[k] = '\0';
      }
    	archive.write(buffer2, fillSize);
    	delete[] buffer2;
    }
    remaining -= chunk_size;

  }
  std::cout << "starting write archive done" << std::endl;
  file.close();
}
void SFile::readArchive(std::fstream &archive, std::vector<int> chunks, std::ofstream &file, int size) {
  int remaining = size;
  int numChunks = chunks.size();
  file.seekp(0);
  for (int i = 0; i < numChunks; i++) {
    int cur_chunk = chunks[i];
    int readSize = (i == numChunks-1) ? remaining : chunk_size;
    archive.seekg(header_size+cur_chunk*chunk_size);
    char* buffer = new char[readSize];
    archive.read(buffer, readSize);
    file.write(buffer, readSize);
    delete[] buffer;
  }
  file.close();
}
//TODO
void SFile::writeWholeArchive(std::fstream& oldArchive, std::ofstream& newArchive, std::vector<block_i> oldBlocks, std::vector<block_i> newBlocks, std::unordered_map<int,int> newOldBlockMap) {
    for (int newIdx = 0; newIdx < newBlocks.size(); newIdx++) {
        if (newOldBlockMap.find(newIdx) != newOldBlockMap.end()) {

            int oldIdx = newOldBlockMap[newIdx];
            int remaining = oldBlocks[oldIdx].size;
            for (int i = 0; i < oldBlocks[oldIdx].chunks.size(); i++) {
                int readSize = (remaining >= chunk_size) ? chunk_size : remaining;
                char* buffer = new char[readSize];
                int oldChunk = oldBlocks[oldIdx].chunks[i];
                int newChunk = newBlocks[newIdx].chunks[i];
                int oldPos = header_size + oldChunk*chunk_size;
                int newPos = header_size + newChunk*chunk_size;
                oldArchive.seekg(oldPos);
                oldArchive.read(buffer, readSize);
                newArchive.seekp(newPos);
                newArchive.write(buffer, readSize);
                delete[] buffer;
                remaining -= readSize;
            }
        }
    }
}

#endif

