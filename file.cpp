//
// Created by Ge Chang on 2018/3/1.
//

#include "file.h"
//#include <iostream>
//#include <fstream>
file::file() {

    version_number = 0.0;
    build_time = "";
    std::fstream myfile; // ifstream, ofstream,
    myfile.open("archive.bin",std::ios::out|std::ios::binary|std::ios::in);
    std::cout << myfile.tellg() << std::endl;
    std::cout << myfile.tellp() << std::endl;
    bool exist = true;
    if (myfile.tellg() == -1) {
        std::cout << "Should Initialize archive.bin file with empty header" << std::endl;
        myfile.close();
        std::ofstream myfile1;
        myfile1.open("archive.bin", std::ios::out|std::ios::app);
        this->initHeader(myfile1);
        myfile1.close();
        exist = false;
    }
    if (!exist) {
        myfile.open("archive.bin", std::ios::out|std::ios::binary|std::ios::in);
    }
    myfile.close();

}
void file::initHeader(std::ofstream &file) {
    char* s = new char[1024];
    for (int i = 0; i < 1024; i++) {
        s[i] = ' ';
    }
    file.write(s, 1024);
    delete[] s;
}
file::~file() {

}

file &file::add(std::string type, std::string name) {
    return *this;
}

file &file::del(std::string type, std::string name) {
    return *this;
}

void file::l(std::string content) {

}

void file::l(){

}

void file::search(std::string content) {

}

void file::version() {

}

void file::error() {

}

void file::info() {

}
