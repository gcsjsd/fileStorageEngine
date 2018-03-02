//
// Created by Ge Chang on 2018/3/1.
//

#include "file.h"

file::file() {
    std::ofstream myfile;
    myfile.open("archive.bin",std::ios::out|std::ios::app);
    myfile.close();
}

file::file(const file &other) {

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
