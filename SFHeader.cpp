#include "SFHeader.h"
#include <iostream>
#include <unordered_set>
#include <unordered_map>

SFHeader::SFHeader() {
}


SFHeader::~SFHeader() {
}

std::vector<int> SFHeader::assignChunks(int chunkNum) {
    std::cout << "beginning assign chunks" << std::endl;
    std::vector<int> res;
    std::unordered_set<int> used;
    std::cout << sizeof(this->blocks) / sizeof(block_i) << std::endl;
    for (int i = 0; i < sizeof(this->blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            std::cout << i << std::endl;
            std::cout << "chunk num: " << this->blocks[i].chunks.size() << std::endl;
            for (int j = 0; j < this->blocks[i].chunks.size(); j++) {
                used.insert(this->blocks[i].chunks[j]);
            }
        }
    }
    std::cout << "beginning assign chunks2" << std::endl;
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
    std::cout << size << std::endl;
    int chunkNum = size / chunk_size;
    if (size % chunk_size != 0) {
        chunkNum++;
    }
    std::cout << chunkNum << std::endl;
    std::vector<int> assignedChunks = this->assignChunks(chunkNum);
    std::cout << "assigned done" << std::endl;
    for (int i = 0; i < chunkNum; i++) {
        block.chunks.push_back(assignedChunks[i]);
        std::cout << assignedChunks[i] << std::endl;
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
    //std::cout << writeSize << std::endl;
    archive.write((char*)&block, writeSize);
    return assignedChunks;
}
void SFHeader::delFileHeader(int atype, std::string aname, std::fstream& archive) {
    int blockIdx = 0;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        int type = this->blocks[i].type;
        std::string name(this->blocks[i].name);
        if (type == atype && name == aname) {
            this->blocks[i].type = AVA;
            blockIdx = i;
            break;
        }
    }
    int pos = blockIdx*block_size;
    int writeSize = block_size;
    archive.seekp(pos);
    archive.write((char*)&(this->blocks[blockIdx]), writeSize);
}

std::vector<int> SFHeader::getFile(int atype, std::string aname) {
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        int type = this->blocks[i].type;
        std::string name(this->blocks[i].name);
        if (type == atype && name == aname && this->blocks[i].type != AVA) {
            return this->blocks[i].chunks;
        }
    }
    return {};
}


int SFHeader::getFileSize(int atype, std::string aname) {
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        int type = this->blocks[i].type;
        std::string name(this->blocks[i].name);
        if (type == atype && name == aname && this->blocks[i].type != AVA) {
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
void SFHeader::updateWholeHeader(std::fstream& archive) {
    int usedChunks = 0;
    int neededChunks = 0;
    archive.seekg(0, std::ios::end);
    int size = (int)archive.tellg() - header_size;
    usedChunks = size / chunk_size;
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
            neededChunks += (this->blocks[i].chunks.size());
        }
    }
    if (usedChunks > neededChunks*2) {
        std::vector<block_i> newBlocks;
        for (int i = 0; i < maxFileNumber; i++) {
            newBlocks[i].type = AVA;
            for (int j = 0; j < name_size; j++) {
                newBlocks[i].name[j] = 'x';
            }
            newBlocks[i].type = AVA;
            newBlocks[i].size = 0;
//            newBlocks[i].date = __DATE__;
        }
        int newPtr = 0;
        int chunkPtr = 0;
        std::unordered_map<int, int> newOldBlockMap;
        for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
            if (this->blocks[i].type != AVA) {
                for (int j = 0; j < this->blocks[i].chunks.size(); j++) {
                    newBlocks[newPtr].chunks.push_back(chunkPtr);
                    chunkPtr++;
                }
                newBlocks[newPtr].type = this->blocks[i].type;
                for (int j = 0; j < name_size; j++) {
                    newBlocks[newPtr].name[j] = this->blocks[i].name[j];
                }
                newBlocks[newPtr].day = this->blocks[i].day;
                newBlocks[newPtr].month = this->blocks[i].month;
                newBlocks[newPtr].year = this->blocks[i].year;
                newOldBlockMap[newPtr] = i;
                newBlocks[newPtr].size = this->blocks[i].size;
                newBlocks[newPtr].type = this->blocks[i].type;
                newPtr++;
            }
        }
      //TODO
      /* 0.create new archive, write header to new archive.
       *
       * 1.write content to new archive by calling SFile.writeWholeArchive()
       * 2.delete old archive, rename new archive to archive.bin.
       */

    }
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
                std::cout << this->blocks[i].name << " " << this->blocks[i].size <<"byte " << this->blocks[i].day << "/" << this->blocks[i].month << "/" << this->blocks[i].year << std::endl;
            }
        }
    }
    return;
}

void SFHeader::listFiles() {
    for (int i = 0; i < sizeof(blocks)/sizeof(block_i); i++) {
        if (this->blocks[i].type != AVA) {
                std::cout << this->blocks[i].name << " " << this->blocks[i].size <<"byte " << this->blocks[i].day << "/" << this->blocks[i].month << "/" << this->blocks[i].year << std::endl;
        }
    }
    return;
}

int SFHeader::typeI2S(std::string type){
    if(type=="txt") return TXT;
    else if(type=="pic") return PIC;
    else if(type=="bin") return BIN;
    else return -1;
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
    for (int j = 0; j < this->blocks[i].chunks.size(); j++) {
      std::cout << this->blocks[i].chunks[j] << ", ";
    }
    std::cout << std::endl;
    std::cout << "day: " << this->blocks[i].day << std::endl;
  }
}
