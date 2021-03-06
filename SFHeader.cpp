#include "SFHeader.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>

SFHeader::SFHeader() {
}


SFHeader::~SFHeader() {
}

std::vector<int> SFHeader::assignChunks(int chunkNum) {
    std::vector<int> res;
    std::unordered_set<int> used;

    for (int i = 0; i < sizeof(this->blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            int totalChunks = 0;
            int j = 0;
            while (totalChunks != sizeof(this->blocks[i].chunks) / sizeof(short) && this->blocks[i].chunks[j] != -1 ) {
              j+= 1;
              totalChunks+=1;
            }

          for (int j = 0; j < totalChunks; j++) {

                used.insert(this->blocks[i].chunks[j]);
            }
        }
    }

    int cur_chunk = 0;
    int assigned = 0;
    while (assigned != chunkNum) {
        if (used.find(cur_chunk) == used.end()) {
            res.push_back(cur_chunk);
            assigned++;
        }
        cur_chunk++;
    }
    return res;
}

std::vector<int> SFHeader::addFileHeader(block_i &block, std::fstream& archive) {
    int size = block.size;
    int chunkNum = size / chunk_size;
    if (size % chunk_size != 0) {
        chunkNum++;
    }
    std::vector<int> assignedChunks = this->assignChunks(chunkNum);
    for (int i = 0; i < chunkNum; i++) {
        block.chunks[i] = (short)assignedChunks[i];
    }
    int blockIdx = 0;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type == AVA) {
            blockIdx = i;
            break;
        }
    }
    int pos = blockIdx*block_size;
    int writeSize = block_size;
    archive.seekp(pos);
    archive.write((char*)&block, writeSize);
    return assignedChunks;
}

bool SFHeader::delFileHeader(std::string filename, std::fstream& archive) {
    int blockIdx = 0;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        std::string name(this->blocks[i].name);
        if (name == filename) {
            this->blocks[i].type = AVA;
            blockIdx = i;
            break;
        }
    }
    int pos = blockIdx*block_size;
    int writeSize = block_size;
    archive.seekp(pos);
    archive.write((char*)&(this->blocks[blockIdx]), writeSize);
    int usedChunks = 0;
    int neededChunks = 0;
    archive.seekg(0, std::ios::end);
    int size = (int)archive.tellg() - header_size;
    usedChunks = size / chunk_size;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            int totalChunks = 0;
            while (totalChunks < sizeof(this->blocks[i].chunks) / sizeof(short) && this->blocks[i].chunks[totalChunks] != -1) {
              totalChunks++;
            }
            neededChunks += totalChunks;
        }
    }
    if (usedChunks > neededChunks*2)
      return true;
    else
      return false;
}

std::vector<int> SFHeader::getFile(std::string aname) {
    std::vector<int> res;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        int type = this->blocks[i].type;
        std::string name(this->blocks[i].name);
        if (type != AVA && name == aname && this->blocks[i].type != AVA) {
            //return this->blocks[i].chunks;
            int idx = 0;
            while (idx < sizeof(this->blocks[i].chunks)/sizeof(short) && this->blocks[i].chunks[idx] != -1) {
              res.push_back((int)this->blocks[i].chunks[idx]);
              idx++;
            }
            return res;
        }
    }
    return {};
}

std::vector<std::string> SFHeader::getFileName() {
  std::vector<std::string> res;
  for (int i = 0; i < sizeof(blocks) / sizeof(block_i); i++) {
    int type = this->blocks[i].type;
    std::string name(this->blocks[i].name);
    if (type != AVA) {
      res.push_back(name);
    }
  }
  return res;
}
int SFHeader::getFileSize(std::string aname) {
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        int type = this->blocks[i].type;
        std::string name(this->blocks[i].name);
        if (type != AVA && name == aname && this->blocks[i].type != AVA) {
            return this->blocks[i].size;
        }
    }
    return -1;
}


void SFHeader::readHeader(std::fstream& archive) {
    archive.seekg(0);
    archive.read((char*)&(this->blocks), header_size);
}
void SFHeader::writeHeader(std::fstream& archive) {
    archive.seekp(0);
    archive.write((char*)&(this->blocks), header_size);
}

void SFHeader::update(std::fstream& archive, std::fstream& newarchive, SFHeader& other) {
      int newPtr = 0;
      int chunkPtr = 0;
      std::unordered_map<int, int> newOldBlockMap;
      for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
          if (this->blocks[i].type != AVA) {
              block_i& b = other.getBlock(newPtr);
              int totalChunks = 0;
              while (totalChunks < sizeof(this->blocks[i].chunks) / sizeof(short) && this->blocks[i].chunks[totalChunks] != -1) {
                  totalChunks++;
              }
              for (int j = 0; j < totalChunks; j++) {
                  b.chunks[j] = (chunkPtr);
                  chunkPtr++;
              }
              b.type = this->blocks[i].type;
              for (int j = 0; j < name_size; j++) {
                  b.name[j] = this->blocks[i].name[j];
              }
              b.day = this->blocks[i].day;
              b.month = this->blocks[i].month;
              b.year = this->blocks[i].year;
              newOldBlockMap[newPtr] = i;
              b.size = this->blocks[i].size;
              b.type = this->blocks[i].type;
              newPtr++;
          }
      }
      std::vector<block_i> oldChunks;
      std::vector<block_i> newChunks;
      for (int i = 0; i < sizeof(blocks) / sizeof(block_i); i++) {
        oldChunks.push_back(getBlock(i));
        newChunks.push_back(other.getBlock(i));
      }
      other.writeHeader(newarchive);
      SFile::writeWholeArchive(archive, newarchive, oldChunks, newChunks, newOldBlockMap);
}


bool contains(char* name, std::string s) { //TODO: check if the name contains string s.
    std::string tmp(name);
    size_t pos = tmp.find(s);
    if(pos==std::string::npos) return false;
    else return true;
}
void SFHeader::listFiles(std::string s) {
    // go through this->blocks, check file name, list.
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            if (contains(this->blocks[i].name, s)) {
                std::cout << this->blocks[i].name << " " << this->blocks[i].size <<"byte " << this->blocks[i].month << "/" << this->blocks[i].day << "/"  << this->blocks[i].year << std::endl;
            }
        }
    }
    return;
}

void SFHeader::listFiles() {
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            std::cout << this->blocks[i].name << " " << this->blocks[i].size <<"byte " << this->blocks[i].month << "/" << this->blocks[i].day << "/"  << this->blocks[i].year << std::endl;

        }
    }
    return;
}

int SFHeader::typeI2S(std::string fileName){
    std::size_t pos = fileName.find(".");
    std::string type = fileName.substr(pos+1,3);
    if(type=="txt") return TXT;
    else return OTH;
}

std::string SFHeader::typeS2I(int atype){
    if(atype==1) return "txt";
    else if(atype==2) return "bin";
    else if(atype==3) return "pic";
    else if(atype==0) return "void";
    else if(atype==4) return "deleted";
    else return "error";
}

/*
 * Print the header. Used for test
 */
void SFHeader::printHeader() {
  for (int i = 0; i < maxFileNumber; i++) {
    std::cout << "type: " << this->blocks[i].type << std::endl;
    std::cout << "name: " << this->blocks[i].name << std::endl;
    std::cout << "size: " << this->blocks[i].size << " bytes" << std::endl;
    std::cout << "chunks: ";
    int totalChunks = 0;
    while (totalChunks < sizeof(this->blocks[i].chunks) / sizeof(short) && this->blocks[i].chunks[totalChunks] != -1) {
      totalChunks++;
    }
    for (int j = 0; j < totalChunks; j++) {
      std::cout << this->blocks[i].chunks[j] << ", ";
    }
    std::cout << std::endl;
    std::cout << "day: " << this->blocks[i].day << std::endl;
  }
}


std::vector<std::string> SFHeader::find_txt_Files() {
	std::vector<std::string> res;
	for (int i = 0; i < sizeof(blocks) / sizeof(block_i); i++) {
		std::string name(this->blocks[i].name);
		if (this->blocks[i].type == TXT) {
			res.push_back(name);
			}
		}			
	return res;
}

block_i& SFHeader::getBlock(int i) {
  return blocks[i];
}
