//
// Created by Ge Chang on 2018/3/1.
//

#include "file.h"

file::file() {
    version_number = 0.1;
    build_time = __DATE__;
    //chunk_size = 1024*50;
    std::ofstream myfile;
    myfile.open("archive.bin",std::ios::out|std::ios::app);
    myfile.close();
}

file::~file() {
}

file &file::add(std::string type, std::string name) {
    std::ifstream infile(name, std::ifstream::binary);
    std::filebuf* pbuf = infile.rdbuf();
    std::size_t size = pbuf->pubseekoff(0,infile.end,infile.in);
    pbuf->pubseekpos(0,infile.in);

    std::ofstream myfile("archive.bin",std::ios::out|std::ios::app);
    char* buffer=new char[size];
    pbuf->sgetn(buffer, size);
    std::cout.write(buffer,size);
    myfile<<buffer;
    delete[] buffer;
    infile.close();
    myfile.close();
    //std::cout<<"finish"<<std::endl;
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
    std::cout<<"sfarchiver version: "<<version_number<<" "<<build_time<<std::endl;
    return;

}

void file::error() {

}

void file::info() {

}
