//
// Created by Ge Chang on 2018/3/1.
//

#ifndef SFARCHIVE_H
#define SFARCHIVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
class SFArchive {
private:
    float version_number;
    std::string build_time;
public:
    SFArchive();
    ~SFArchive();
    SFArchive& add(std::string type, std::string name); // ./sf add type file
    SFArchive& del(std::string type, std::string name); // ./sf del type file
    void l(std::string content); // ./sf l content
    void l(); // ./sf l
    void search(std::string content); // ./sf search content
    void version(); //./sf -v
    void error();
    void info();
    void initHeader(std::ofstream &file);

};


#endif //FILESTORAGE_FILE_H
