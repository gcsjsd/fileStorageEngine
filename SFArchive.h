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
#include "SFile.h"

class SFArchive {
public:
    //static float version_number;
    //static std::string build_time;
    std::fstream archive;

public:
    SFArchive(std::string archiveName); //initialize the SFArchive
    ~SFArchive(); // close the .bin file

    SFArchive& add(std::string name); // ./sf add type file :: u cant add the file with the same name twice

    SFArchive& del(std::string name); // ./sf del type file :: set the flag in the header

    SFArchive& extract(std::string name);

    void list(std::string content); // ./sf l content :: show the list of the file whose title has string of "content"

    void list(); // ./sf l :: show the list of all files

    void search(std::string content); // ./sf search content :: search the txt files whose content has this string

    static void version(); //./sf -v :: version + compile date

    //the metadata for a file in the header

    static void error(); // :: show error type (invalid arg, insufficient arg)
    
    static void info() {
        std::cout<<"Usage: ./sfarchiver <command>"<<std::endl<<std::endl;
        std::cout<<"./sfarchiver add typename filename   "<<"add a txt, pic or bin file"<<std::endl;
        std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
        std::cout<<"./sfarchiver -l (filename)           "<<"list files (matching given name)"<<std::endl;
        std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
        std::cout<<"./sfarchiver extract filename        "<<"extract a file"<<std::endl;
        std::cout<<"./sfarchiver find content            "<<"search txt files matching the given content"<<std::endl;
        std::cout<<"./sfarchiver -v                      "<<"show the version of this app"<<std::endl;
    }

    void initHeader(std::ofstream &file); // fulfill the header.
    //block_i* readerHeader(); // read all the header into the struct
    //void updateHeader(block_i* blocks); // update the header,

};
/*
class information {
private: 
    void info(){
        std::cout<<"Usage: ./sfarchiver <command>"<<std::endl<<std::endl;
        std::cout<<"./sfarchiver add typename filename   "<<"add a txt, pic or bin file"<<std::endl;
        std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
        std::cout<<"./sfarchiver -l (filename)           "<<"list files (matching given name)"<<std::endl;
        std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
        std::cout<<"./sfarchiver extract filename        "<<"extract a file"<<std::endl;
        std::cout<<"./sfarchiver find content            "<<"search txt files matching the given content"<<std::endl;
        std::cout<<"./sfarchiver -v                      "<<"show the version of this app"<<std::endl;
        return;
    }
public:
    information();
    ~information();
    void giveInfo(){
        info();
        return;
    }
};
*/
#endif //FILESTORAGE_FILE_H
