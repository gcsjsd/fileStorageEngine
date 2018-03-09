//
// Created by Ge Chang on 2018/3/1.
//

#include "SFArchive.h"
#include <vector>
SFArchive::SFArchive() {

    //version and compile time
    version_number = 0.0;
    build_time = __DATE__;

    //open create the arch.bin if it exists
    this->archive.open("archive.bin",std::ios::out|std::ios::binary|std::ios::in);
    std::cout << archive.tellg() << std::endl;
    std::cout << archive.tellp() << std::endl;
    bool exist = true; // the .bin file has existed

    // if .bin doesnt exist, create the file
    if (this->archive.tellg() == -1) {
        std::cout << "Should Initialize archive.bin file with empty header" << std::endl;
        this->archive.close();
        std::ofstream archive1;
        archive1.open("archive.bin", std::ios::out|std::ios::app);
        this->initHeader(archive1); //initialize the header of the file
        archive1.close();
        exist = false;
    }

    // if just created, open this file again.
    if (!exist) {
        this->archive.open("archive.bin", std::ios::out|std::ios::binary|std::ios::in);
    }


}

void SFArchive::initHeader(std::ofstream &file) {
    block_i blocks[maxFileNumber]; // current we can write 20 files at most
    for(int i=0;i<maxFileNumber;i++){
        blocks[i].type = AVA;
        for(int j=0; j<name_size; j++){
            blocks[i].name[j] = 'x';
        }
        blocks[i].exist = false;
        blocks[i].size = 0;
//        blocks[i].date = __DATE__;
    }

    file.write((char*)&blocks, sizeof(blocks));

}

SFArchive::~SFArchive() {
    this->archive.close();
}
SFArchive& SFArchive::add(std::string type, std::string name) {
    /* 0.Init SFHeader header.
     * 1.open the file, create block for this file.
     * 2.addFileHeader, all archive header operation is done.
     * 3.call SFile.writeArchive(archive, vector<int>chunks, file)
     */
	SFHeader header;
	header.readHeader(this->archive);
        return *this;
}

SFArchive& SFArchive::del(std::string type, std::string name) {
    /* 0.Init SFHeader header
     * 1.call header.delFileHeader().
     * 2.Things are done
     */
   return *this;
}

SFArchive& SFArchive::extract(std::string type, std::string name) {
    /* 0.Init SFHeader header
     * 1.ofstream open file
     * 2.call header.getFile()
     * 3.call header.getFileSize()
     * 4.call SFile.readArchive(archive, vector<int>chunks, file, size)
     */
    return *this;
}

void SFArchive::list(std::string content) {
    /* 0.Init SFHeader header
     * 1.call header.listFiles(content)
     */

}

void SFArchive::list(){
/* 0.Init SFHeader header
 * 1.call header.listFiles()
 */
}

void SFArchive::search(std::string content) {
    /*
     *
     */
}

void SFArchive::version() {

}

void SFArchive::error() {

}

void SFArchive::info() {

}
