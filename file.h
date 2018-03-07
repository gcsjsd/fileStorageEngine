//
// Created by Ge Chang on 2018/3/1.
//

#ifndef FILESTORAGE_FILE_H
#define FILESTORAGE_FILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <cassert>

// data structure of the meta data:
//first part:  imap: filetype, file name, file size, first chunk, chunk number.
class file {
private:
    float version_number;
    std::string build_time;
    //int chunk_size;

public:
    file();
    ~file();
    file& add(std::string type, std::string name); // ./sf add type file
    file& del(std::string type, std::string name); // ./sf del type file
    void l(std::string content); // ./sf l content
    void l(); // ./sf l
    void search(std::string content); // ./sf search content
    void version(); //./sf -v
    void error();
    void info();


};


#endif //FILESTORAGE_FILE_H
