//
// Created by Ge Chang on 2018/3/1.
//

#include "SFArchive.h"
#include <vector>
//#include <iostream>
//#include <fstream>
SFArchive::SFArchive() {

    //version and compile time
    version_number = 0.0;
    build_time = __DATE__;

    //open create the arch.bin if it exists
    this->archive.open("archive.bin",std::ios::out|std::ios::binary|std::ios::in);
    std::cout << myfile.tellg() << std::endl;
    std::cout << myfile.tellp() << std::endl;
    bool exist = true; // the .bin file has existed

    // if .bin doesnt exist, create the file
    if (this->archive.tellg() == -1) {
        std::cout << "Should Initialize archive.bin file with empty header" << std::endl;
        this->archive.close();
        std::ofstream archive1;
        archive1.open("archive.bin", std::ios::out|std::ios::app);
        this->initHeader(archive1); //initialize the header of the file
        archive1.close();
        exist = false;
    }

    // if just created, open this file again.
    if (!exist) {
        this->archive.open("archive.bin", std::ios::out|std::ios::binary|std::ios::in);
    }


}

void SFArchive::initHeader(std::ofstream &file) {
    //char* s = new char[chunk_size]; //set the space of the header
    block_i blocks[50]; // current we can write 50 files at most

    for(std::size_t i=0;i<50;i++){
        //to do:: fill the empty header
        blocks[i].type = AVA;
        for(int j=0; j<name_size; j++){
            blocks[i].name[j] = 'x';
        }
        blocks[i].size = 0;
        blocks[i].date = __DATE__;
        // do we need to initialize the vector?
    }
    this->archive.write((char*)&blocks, sizeof(blocks));
    //delete[] s;
}

SFArchive::~SFArchive() {
    this->archive.close();
}

SFArchive& SFArchive::add(std::string type, std::string name) {
    std::ifstream file(name, std::ios::in|std::ios|binary|std::ios::ate);
    if (file.is_open()) {
        int size = file.tellg();
        file.seekg(0, std::ios::beg);
        int chunkSize = 1024;
        int chunkNum = size / 1024;
        if (size % 1024 != 0) {
            chunkNum += 1;
        }
        char* headerChar = new char[1024];
        this->archive.read(headerChar, 1024);
        SFHeader header(headerChar);
        vector<int> assignedChunks = header.assignChunks(chunkNum);
        SFile sfile(type, name, size);
        char* content = new char[size];
        sfile.writeArchive(this->archive, assignedChunks, content);
        this->archive.close();


    } else {
        std::cout << "ERROR: file open failed!" << std::endl;
    }
    return *this;
}

SFArchive& SFArchive::del(std::string type, std::string name) {
    return *this;
}

void SFArchive::l(std::string content) {

}

void SFArchive::l(){

}

void SFArchive::search(std::string content) {

}

void SFArchive::version() {

}

void SFArchive::error() {

}

void SFArchive::info() {

}
