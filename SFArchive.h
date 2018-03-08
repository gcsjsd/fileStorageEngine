//
// Created by Ge Chang on 2018/3/1.
//

#ifndef SFARCHIVE_H
#define SFARCHIVE_H

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "SFHeader.h"


class SFArchive {
private:
    float version_number;
    std::string build_time;
    std::fstream archive;

public:
    SFArchive(); //initialize the SFArchive
    ~SFArchive(); // close the .bin file

    SFArchive& add(std::string type, std::string name); // ./sf add type file :: u cant add the file with the same name twice

    SFArchive& del(std::string type, std::string name); // ./sf del type file :: set the flag in the header

    SFArchive& extract(std::string type, std::string name);

    void list(std::string content); // ./sf l content :: show the list of the file whose title has string of "content"

    void list(); // ./sf l :: show the list of all files

    void search(std::string content); // ./sf search content :: search the txt files whose content has this string

    void version(); //./sf -v :: version + compile date

    //the metadata for a file in the header

    void error(); // :: show error type (invalid arg, insufficient arg)
    void info(); // :: show the information

    void initHeader(std::ofstream &file); // fulfill the header.
    //block_i* readerHeader(); // read all the header into the struct
    //void updateHeader(block_i* blocks); // update the header,

};


#endif //FILESTORAGE_FILE_H
