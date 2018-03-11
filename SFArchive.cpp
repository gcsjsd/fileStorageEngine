//
// Created by Ge Chang on 2018/3/1.
//

#include "SFArchive.h"
#include <vector>
#include <stdio.h>
SFArchive::SFArchive(std::string archiveName) {

    //version and compile time
    //version_number = 0.0;
    //build_time = __DATE__;

    //open create the arch.bin if it exists
    this->archiveName = archiveName;
    this->archive.open(archiveName,std::ios::out|std::ios::binary|std::ios::in);
    bool exist = true; // the .bin file has existed
    // if .bin doesnt exist, create the file
    if (this->archive.tellg() == -1) {
        std::cout << "Creating archive..." << archiveName << std::endl;
        this->archive.close();
        std::ofstream archive1;
        archive1.open(archiveName, std::ios::out|std::ios::app);
        this->initHeader(archive1); //initialize the header of the file
        archive1.close();
        exist = false;
        std::cout << "Creating archive done." << std::endl;
    }

    // if just created, open this file again.
    if (!exist) {
        this->archive.open(archiveName, std::ios::out|std::ios::binary|std::ios::in);
    }

}

void SFArchive::initHeader(std::ofstream &file) {
    block_i blocks[maxFileNumber]; // current we can write 20 files at most
    for(int i=0;i<maxFileNumber;i++){
        blocks[i].type = AVA;
        for(int j=0; j<name_size; j++){
            blocks[i].name[j] = 'x';
        }
        blocks[i].size = 0;

        blocks[i].day = 1;
        blocks[i].month = 1;
        blocks[i].year = 2000;
        for (int j = 0; j < 100; j++) {
          blocks[i].chunks[j] = -1;
        }
    }

    file.write((char*)&blocks, sizeof(blocks));

}

SFArchive::~SFArchive() {
    this->archive.close();
}
SFArchive& SFArchive::add(std::string name) {
    /* 0.Init SFHeader header.
     * 1.open the file, create block for this file.
     * 2.addFileHeader, all archive header operation is done.
     * 3.call SFile.writeArchive(archive, vector<int>chunks, file)
     */
	SFHeader header;
	header.readHeader(this->archive);
  block_i block;
  for (int j = 0; j < 100; j++) {
    block.chunks[j] = -1;
  }
  int type = header.typeI2S(name);
  block.type = type;
  const char* s = name.c_str();
  int i = 0;
  while (s[i] != '\0') {
    block.name[i] = s[i];
    i++;
  }
  while (i != 32) {
    block.name[i] = '\0';
    i++;
  }
  std::ifstream file1(name);
  if (file1.tellg()==-1) {
    std::cout << "file " << name << " doesn't exist!" << std::endl;
    file1.close();
    return *this;
  }
  file1.close();
  std::ifstream file (name,  std::ios::in | std::ios::ate | std::ios::binary);
  int size = file.tellg();
  block.size = size;
  std::cout << "adding file to archive ..." << std::endl;
  time_t t = time(0);
  struct tm *now = localtime(&t);
  block.day = now->tm_mday;
  block.month = now->tm_mon+1;
  block.year = now->tm_year+1900;

  std::vector<int> chunks = header.addFileHeader(block, this->archive);
  file.seekg(0);
  SFile::writeArchive(this->archive, chunks, file, size);
  std::cout << "add file done" << std::endl;
  return *this;
}

SFArchive& SFArchive::del(std::string name) {
    /* 0.Init SFHeader header
     * 1.call header.delFileHeader().
     * 2.Things are done
     */
   SFHeader header;
   header.readHeader(this->archive);
   bool needDel = header.delFileHeader(name, this->archive);
   if (needDel) {
     std::string newName = this->archiveName + ".temp";
     std::ofstream initStream;
     initStream.open(newName, std::ios::out | std::ios::app);
     initHeader(initStream);
     initStream.close();
     std::fstream newStream;
     newStream.open(newName, std::ios::out|std::ios::binary|std::ios::in);
     SFHeader newHeader;
     newHeader.readHeader(newStream);
     header.update(this->archive, newStream, newHeader);
     this->archive.close();
     newStream.close();

     if(remove(archiveName.c_str()) != 0 )
       perror( "Error deleting file\n" );

     int ret;
     const char* oldname = newName.c_str();
     const char* newname = this->archiveName.c_str();

     ret = rename(oldname, newname);

     if(ret != 0)
      printf("Error: unable to rename the file\n");

   }
   return *this;
}

SFArchive& SFArchive::extract(std::string name) {
    /* 0.Init SFHeader header
     * 1.ofstream open file
     * 2.call header.getFile()
     * 3.call header.getFileSize()
     * 4.call SFile.readArchive(archive, vector<int>chunks, file, size)
     */

    SFHeader header;
    header.readHeader(this->archive);

    //check if the file exists, read the size and the chunk;
    std::vector<int> chunks;
    //int atype = header.typeI2S(type);
    chunks = header.getFile(name);
    if(chunks.size()==0){
        std::cout<<"this file doesn't exist or has been deleted."<<std::endl;
        return *this;
    }

    int fileSize = header.getFileSize(name);
    
    SFile sfile;
    std::ofstream extractFile(name);
    sfile.readArchive(this->archive, chunks, extractFile, fileSize);
    extractFile.close();
    std::cout << "extract done" << std::endl;
    return *this;

}

void SFArchive::list(std::string content) {
    /* 0.Init SFHeader header
     * 1.call header.listFiles(content)
     */
    //read header
    SFHeader header;
    header.readHeader(this->archive);
    header.listFiles(content);
    return;

}

void SFArchive::list(){
/* 0.Init SFHeader header
 * 1.call header.listFiles()
 */
  SFHeader header;
  header.readHeader(this->archive);
  header.listFiles();
  return;
}

void SFArchive::search(std::string content) {
    /*1.call find_txt_Files()
     *2.call  header.getFile()
	 *3.found->call Header.list()
     */
	SFHeader header;
	bool found = false;
	header.readHeader(this->archive);
	std::vector<std::string> TXTFiles;
	TXTFiles = header.find_txt_Files();
	for (std::string txtName : TXTFiles) {
		std::vector<int>txtFile;
		txtFile = header.getFile(txtName);
		for (int i : txtFile) {
			archive.seekg(0);
			archive.seekg(header_size + i * chunk_size);
			std::istreambuf_iterator<char>begin(archive);
			archive.seekg(header_size + i * chunk_size+chunk_size);
			std::istreambuf_iterator<char>end(archive);
			std::string txt(begin, end);
			if (txt.find(content) != std::string::npos) {
				header.listFiles(txtName);
				found = true;
				break;
			}
		}
	}
	if (!found)std::cout << content << " doesn't exist." << std::endl;
}

void SFArchive::version() {
    std::cout<<"SFArchive version "<<1.0<<__DATE__<<std::endl;
}

void SFArchive::error() {
    std::cout<<"invalid arguments, use ./sfarchiver for more information"<<std::endl;
}


