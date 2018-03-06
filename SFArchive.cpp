//
// Created by Ge Chang on 2018/3/1.
//

#include "SFArchive.h"
#include <vector>
//#include <iostream>
//#include <fstream>
SFArchive::SFArchive() {

    version_number = 0.0;
    build_time = "";
    std::fstream archive = this->archive; // ifstream, ofstream,
    archive.open("archive.bin",std::ios::out|std::ios::binary|std::ios::in);
    std::cout << myfile.tellg() << std::endl;
    std::cout << myfile.tellp() << std::endl;
    bool exist = true;
    if (archive.tellg() == -1) {
        std::cout << "Should Initialize archive.bin file with empty header" << std::endl;
        archive.close();
        std::ofstream archive1;
        archive1.open("archive.bin", std::ios::out|std::ios::app);
        this->initHeader(archive1);
        archive1.close();
        exist = false;
    }
    if (!exist) {
        archive.open("archive.bin", std::ios::out|std::ios::binary|std::ios::in);
    }


}
void SFArchive::initHeader(std::ofstream &file) {
    char* s = new char[1024];
    for (int i = 0; i < 1024; i++) {
        s[i] = ' ';
    }
    file.write(s, 1024);
    delete[] s;
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
