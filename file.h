//
// Created by Ge Chang on 2018/3/1.
//

#ifndef FILESTORAGE_FILE_H
#define FILESTORAGE_FILE_H

#include <iostream>
#include <fstream>
#include <string>

class file {
private:
public:
    file();
    file(const file& other);
    ~file();
    file& add(std::string type, std::string name); // ./sf add type file
    file& del(std::string type, std::string name); // ./sf del type file
    void l(std::string content); // ./sf l content
    void l();
    void search(std::string content);
    void version();
    void error();


};


#endif //FILESTORAGE_FILE_H
