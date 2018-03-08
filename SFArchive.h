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

#define AVA 0
#define TXT 1
#define BIN 2
#define PIC 3
#define DEL 4

#define chunk_size 1024
#define block_size 0
#define name_size 20

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

    void l(std::string content); // ./sf l content :: show the list of the file whose title has string of "content"

    void l(); // ./sf l :: show the list of all files

    void search(std::string content); // ./sf search content :: search the txt files whose content has this string

    void version(); //./sf -v :: version + compile date

    //the metadata for a file in the header
    typedef struct block{
        int type; //AVA, TXT, BIN, PIC, DEL
        char name[name_size]; // file name
        int size;// file size
        std::vector<int> chunks;// chunks it has
        std::string date;// create date ? maybe stored in more efficient way
    }block_i;

    void error(); // :: show error type (invalid arg, insufficient arg)
    void info(); // :: show the information

    void initHeader(std::ofstream &file); // fulfill the header.

};


#endif //FILESTORAGE_FILE_H
