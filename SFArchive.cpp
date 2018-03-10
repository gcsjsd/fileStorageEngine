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
    //std::cout << archive.tellg() << std::endl;
    //std::cout << archive.tellp() << std::endl;
    bool exist = true; // the .bin file has existed
    // if .bin doesnt exist, create the file
    if (this->archive.tellg() == -1) {
        std::cout << "Creating archive..." << std::endl;
        this->archive.close();
        std::ofstream archive1;
        archive1.open("archive.bin", std::ios::out|std::ios::app);
        this->initHeader(archive1); //initialize the header of the file
        archive1.close();
        exist = false;
        std::cout << "Creating archive done." << std::endl;
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
SFArchive& SFArchive::add(std::string type, std::string name) {
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
  block.type = PIC; //TODO: what's type ?
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
  std::ifstream file (name,  std::ios::in | std::ios::ate | std::ios::binary);
  int size = file.tellg();
  block.size = size;
  
  time_t t = time(0);
  struct tm *now = localtime(&t);
  block.day = now->tm_mday;
  block.month = now->tm_mon+1;
  block.year = now->tm_year+1900;

  //std::cout << "size " << block.size << std::endl;
  std::vector<int> chunks = header.addFileHeader(block, this->archive);
  //std::cout << "chunks:" << std::endl;
  /*
  for (int i = 0; i < chunks.size(); i++) {
    std::cout << chunks[i] << " " << std::endl;
  }
   */
  file.seekg(0);
  SFile::writeArchive(this->archive, chunks, file, size);
  //std::cout << "add done" << std::endl;
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
    //return *this;
    
    //read header
    SFHeader header;
    header.readHeader(this->archive);

    //check if the file exists, read the size and the chunk;
    std::vector<int> chunks;
    int atype = header.typeI2S(type);
    chunks = header.getFile(atype, name);
    if(chunks.size()==0||atype==-1){
        std::cout<<"this file doesn't exist or has been deleted."<<std::endl;
        return *this;
    }
    std::cout << "chunks to be extracted.." << std::endl;
    for (int i = 0; i < chunks.size(); i++) {
      std::cout << chunks[i] << " ";
    }
    std::cout << std::endl;
    int fileSize = header.getFileSize(atype, name);
    
    SFile sfile;
    std::ofstream extractFile(name);
    sfile.readArchive(this->archive, chunks, extractFile, fileSize);
    extractFile.close();

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
  //std::cout << "going to list" << std::endl;
  header.listFiles();
  //std::cout << "SFArchive::list() done" << std::endl;
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
		txtFile = header.getFile(1, txtName);
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
    std::cout<<"SFArchive version "<<version_number<<__DATE__<<std::endl;
}

void SFArchive::error() {
    std::cout<<"invalid arguments, use ./sfarchiver for more information"<<std::endl;
}

void SFArchive::info() {
    std::cout<<"Usage: ./sfarchiver <command>"<<std::endl<<std::endl;
    std::cout<<"./sfarchiver add typename filename   "<<"add a txt, pic or bin file"<<std::endl;
    std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
    std::cout<<"./sfarchiver -l (filename)           "<<"list files (matching given name)"<<std::endl;
    std::cout<<"./sfarchiver del typename filename   "<<"delete a file"<<std::endl;
    std::cout<<"./sfarchiver extract filename        "<<"extract a file"<<std::endl;
    std::cout<<"./sfarchiver find content            "<<"search txt files matching the given content"<<std::endl;
    std::cout<<"./sfarchiver -v                      "<<"show the version of this app"<<std::endl;
}

